#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include "ui_settingsdialog.h"
class QSettings;
class SettingsDialog : public QDialog, public Ui::SettingsDialog
{
    Q_OBJECT
public:
    SettingsDialog(QWidget *parent=0);
public slots:
    void accept();
private slots:
    void on_pathButton_clicked();
private:
    QSettings *m_settings;
};

#endif // SETTINGSDIALOG_H
