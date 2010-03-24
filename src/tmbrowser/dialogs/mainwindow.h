/***************************************************************************
 *   Copyright (C) 2009-2010 by Tarabaka Alexander <XpycT.TOP@gmail.com>   *
 *                                                                         *
 *  This file is part of Template Monster Browser.			   *
 *									   *
 *  Template Monster Browser is free software: you can redistribute it 	   *
 *  and/or modify it under the terms of the GNU General Public License as  *
 *  published by the Free Software Foundation, either version 3 of the     *
 *  License, or (at your option) any later version.			   *
 *									   *
 *  Template Monster Browser is distributed in the hope that it will 	   *
 *  be useful, but WITHOUT ANY WARRANTY; without even the implied warranty *
 *  of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the	   *
 *  GNU General Public License for more details.			   *
 *									   *
 *  You should have received a copy of the GNU General Public License      *
 *  along with Template Monster Browser.                                   *
 *  If not, see <http://www.gnu.org/licenses/>.                            *
 ***************************************************************************/
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
