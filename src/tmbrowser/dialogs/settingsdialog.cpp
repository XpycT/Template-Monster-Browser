#include "settingsdialog.h"
#include <QFileDialog>
#include <QSettings>
SettingsDialog::SettingsDialog(QWidget *parent)
        :QDialog(parent)
{
    setupUi(this);
    m_settings = new QSettings(QApplication::organizationName(), QApplication::applicationName());
    setWindowTitle(QString("%1 - %2").arg(QApplication::applicationName())
                   .arg(tr("Preferences")));

    QString path = m_settings->value("templatesDir","").toString();
    pathEdit->setText(path);

    setWindowFlags(windowFlags() ^ Qt::WindowContextHelpButtonHint);
    layout()->setSizeConstraint(QLayout::SetFixedSize);
}
void SettingsDialog::on_pathButton_clicked(){
    QFileDialog::Options options = QFileDialog::DontResolveSymlinks | QFileDialog::ShowDirsOnly;

    QString directory = QFileDialog::getExistingDirectory(this,
                                 tr("Select templates directory"),
                                 pathEdit->text(),
                                 options);
     if (!directory.isEmpty())
         pathEdit->setText(directory);
}
void SettingsDialog::accept(){
    m_settings->setValue("templatesDir",pathEdit->text());
    QDialog::accept();
}
