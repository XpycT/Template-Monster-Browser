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
