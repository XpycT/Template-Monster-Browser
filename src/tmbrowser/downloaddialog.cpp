#include "downloaddialog.h"

#include <QFileInfo>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QString>
#include <QStringList>
#include <QTimer>

DownloadDialog::DownloadDialog(QWidget *parent)
        :QDialog(parent), downloadedCount(0), totalCount(0)
{
    setupUi(this);
    setWindowTitle(QString("%1 - %2").arg(QApplication::applicationName())
                   .arg(tr("downloading images")));

    logEdit->setVisible(false);

    setWindowFlags(windowFlags() ^ Qt::WindowContextHelpButtonHint);
    layout()->setSizeConstraint(QLayout::SetFixedSize);

}
void DownloadDialog::on_detailButton_toggled(){
    detailButton->isChecked()?detailButton->setIcon(QIcon(":/images/arrow_down.png"))
            :detailButton->setIcon(QIcon(":/images/arrow_up.png"));
}
/////////
void DownloadDialog::append(const QStringList &urlList)
{
    foreach (QString url, urlList)
        append(QUrl::fromEncoded(url.toLocal8Bit()));

    if (downloadQueue.isEmpty())
        QTimer::singleShot(0, this, SIGNAL(finished()));
}

void DownloadDialog::append(const QUrl &url)
{
    if (downloadQueue.isEmpty())
        QTimer::singleShot(0, this, SLOT(startNextDownload()));

    downloadQueue.enqueue(url);
    ++totalCount;
}
QString DownloadDialog::saveFileName(const QUrl &url)
{
    QString path = url.path();
    QString basename = QFileInfo(path).fileName();

    if (basename.isEmpty())
        basename = "download.failed";

    if (QFile::exists(basename)) {
        // already exists, don't overwrite
        int i = 0;
        basename += '.';
        while (QFile::exists(basename + QString::number(i)))
            ++i;

        basename += QString::number(i);
    }

    return basename;
}

void DownloadDialog::startNextDownload()
{
    if (downloadQueue.isEmpty()) {        
        logEdit->append(tr("<font style='color:green;font-weight:bold;'>%1/%2 files downloaded successfully </font>.<br/>").arg(downloadedCount).arg(totalCount));
        speedLabel->setText(tr("<font style='color:green;font-weight:bold;'>Done!</font>"));
        closeButton->setText(tr("Close"));
        totalProgress->setValue(totalCount);
        emit finished();
        return;
    }
    totalProgress->setRange(0,totalCount);
    totalProgress->setValue(downloadedCount);

    QUrl url = downloadQueue.dequeue();

    QString filename = saveFileName(url);
    output.setFileName(qApp->applicationDirPath()+"/images/"+filename);
    if (!output.open(QIODevice::WriteOnly)) {
        logEdit->append(tr("<font style='color:red;font-weight:bold'>Problem opening save file '%1' for download '%2': %3</font><br/>")
                        .arg(filename).arg(url.toEncoded().constData())
                        .arg(output.errorString()));

        startNextDownload();
        return;                 // skip this download
    }

    QNetworkRequest request(url);
    currentDownload = manager.get(request);
    connect(currentDownload, SIGNAL(downloadProgress(qint64,qint64)),
            SLOT(downloadProgress(qint64,qint64)));
    connect(currentDownload, SIGNAL(finished()),
            SLOT(downloadFinished()));
    connect(currentDownload, SIGNAL(readyRead()),
            SLOT(downloadReadyRead()));

    // prepare the output
    logEdit->append(tr("Downloading %1...").arg(url.toEncoded().constData()));
    downloadTime.start();
}
void DownloadDialog::downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    fileProgress->setRange(0,bytesTotal);
    fileProgress->setValue(bytesReceived);

    // calculate the download speed
    double speed = bytesReceived * 1000.0 / downloadTime.elapsed();
    QString unit;
    if (speed < 1024) {
        unit = tr("bytes/sec");
    } else if (speed < 1024*1024) {
        speed /= 1024;
        unit = tr("kB/s");
    } else {
        speed /= 1024*1024;
        unit = tr("MB/s");
    }

    speedLabel->setText(QString("%1 %2")
                           .arg(speed, 3, 'f', 1).arg(unit));
    fileProgress->update();
}
void DownloadDialog::downloadFinished()
{
    fileProgress->setRange(0,100);
    fileProgress->setValue(0);
    output.close();

    if (currentDownload->error()) {
        // download failed
        logEdit->append(tr("<font style='color:red;font-weight:bold;'>Failed: %1</font>.<br/>")
                        .arg(currentDownload->errorString()));

    } else {
        logEdit->append(tr("<font style='color:green;font-weight:bold;'>Succeeded</font>.<br/>"));
        ++downloadedCount;
    }

    currentDownload->deleteLater();
    startNextDownload();
}

void DownloadDialog::downloadReadyRead()
{
    output.write(currentDownload->readAll());
}
