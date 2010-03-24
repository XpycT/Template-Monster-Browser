#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtNetwork>
#include <QMainWindow>
#include "ui_mainwindow.h"

class QSettings;
class QSqlDatabase;
class QStandardItemModel;
class QSortFilterProxyModel;
class QListWidget;
class MainWindow : public QMainWindow, public Ui::MainWindow
{
    Q_OBJECT
public:
    MainWindow();
private slots:   
    void on_action_Rescan_triggered();
    void on_action_Preferences_triggered();
    void on_action_Download_images_triggered();
    void on_action_About_triggered();
    void on_openButton_clicked();
    bool rescan();
    void loadTemplates(QString where="");
    void showScreen();
    void downloadImages();
    void resortList(const QString &serial);
private:
    QString pathDir;
    QString thumb;
    QSettings *m_settings;
    QListWidget *tmList;
    QSortFilterProxyModel *proxyModel;
    QStandardItemModel *model;
    QStringList urlList;
protected:
    virtual void closeEvent(QCloseEvent *event);
};

#endif // MAINWINDOW_H
