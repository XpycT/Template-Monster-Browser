_RC_FILE = 1
include(../common/common.pri)
TEMPLATE = app
INCLUDEPATH += .
SOURCES += main.cpp \
    dialogs/mainwindow.cpp \
    dialogs/settingsdialog.cpp \
    downloaddialog.cpp
HEADERS += version.h \
    dialogs/mainwindow.h \
    dialogs/settingsdialog.h \
    downloaddialog.h
FORMS += dialogs/mainwindow.ui \
    dialogs/settingsdialog.ui \
    dialogs/downloaddialog.ui
