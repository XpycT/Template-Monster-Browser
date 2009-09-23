#include <QTextCodec>
#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include "version.h"
#include "dialogs/mainwindow.h"

int main(int argc, char **argv)
{
    QTextCodec *codec = QTextCodec::codecForName("CP1251");
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

