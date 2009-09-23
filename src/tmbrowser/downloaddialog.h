#ifndef DOWNLOADDIALOG_H
#define DOWNLOADDIALOG_H

#include <QDialog>
#include <QFile>
#include <QQueue>
#include <QTime>
#include <QUrl>
#include <QNetworkAccessManager>
#include "ui_downloaddialog.h"
class DownloadDialog : public QDialog, public Ui::DownloadDialog
{
    Q_OBJECT
public:
    DownloadDialog(QWidget *parent=0);

    void append(const QUrl &url);
    void append(const QStringList &urlList);
    QString saveFileName(const QUrl &url);
signals:
    void finished();

private slots:
    void on_detailButton_toggled();

    void startNextDownload();
    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void downloadFinished();
    void downloadReadyRead();

private:
    QNetworkAccessManager manager;
    QQueue<QUrl> downloadQueue;
    QNetworkReply *currentDownload;
    QFile output;
    QTime downloadTime;

    int downloadedCount;
    int totalCount;
};

#endif // DOWNLOADDIALOG_H
