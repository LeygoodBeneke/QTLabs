QT       += core gui core5compat

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    main.cpp \
    finddialog.cpp \

TARGET = Find

TEMPLATE = app

HEADERS += \
    finddialog.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
