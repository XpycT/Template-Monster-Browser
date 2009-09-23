CONFIG += qt
QT +=sql network #webkit
DESTDIR = ../../bin

DEPENDPATH += \
    . \
    ../common \

INCLUDEPATH += \
    . \
    ../common \

CONFIG(debug, debug|release) {
    message(Debug!)
    RCC_DIR = ../../build/$${TARGET}/debug/rcc
    MOC_DIR = ../../build/$${TARGET}/debug/moc
    OBJECTS_DIR = ../../build/$${TARGET}/debug/obj

    mac|unix: TARGET = $$join(TARGET,,,_debug)
    win32: TARGET = $$join(TARGET,,d)
} else {
    message(Release!)
    RCC_DIR = ../../build/$${TARGET}/release/rcc
    MOC_DIR = ../../build/$${TARGET}/release/moc
    OBJECTS_DIR = ../../build/$${TARGET}/release/obj
}
contains(_RC_FILE, 1 ) {
  win32:RC_FILE = $${TARGET}.rc
}
TRANSLATIONS += ../../data/i18n/i18n_en.ts \
                 ../../data/i18n/i18n_ru.ts

RESOURCES += ../../data/tmbrowser.qrc
