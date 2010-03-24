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
