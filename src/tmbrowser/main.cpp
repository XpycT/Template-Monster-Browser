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
#include <QTextCodec>
#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include "version.h"
#include "dialogs/mainwindow.h"

int main(int argc, char **argv)
{
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForTr(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForLocale(codec);

    QApplication app(argc, argv);

    QApplication::setApplicationName(TMBROWSER_NAME);
    QApplication::setApplicationVersion(TMBROWSER_VERSION);
    QApplication::setOrganizationName(TMBROWSER_ORGANIZATION);
    QApplication::setOrganizationDomain(TMBROWSER_DOMAIN);
    QApplication::addLibraryPath(QApplication::applicationDirPath() + "/plugins");

    QString locale = QLocale::system().name();

    QTranslator qtTranslator;
    qtTranslator.load(QString("qt_") + locale, ":/i18n");
    QApplication::installTranslator(&qtTranslator);

    QTranslator translator;
    translator.load(QString("i18n_") + locale, ":/i18n");
    QApplication::installTranslator(&translator);

    MainWindow dlg;
    dlg.show();

    return app.exec();
}

