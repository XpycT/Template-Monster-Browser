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
