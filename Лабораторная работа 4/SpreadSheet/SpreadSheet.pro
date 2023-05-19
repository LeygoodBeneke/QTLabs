TEMPLATE = app
TARGET = SpreadSheet
INCLUDEPATH += .
QT += core5compat gui widgets

DEFINES += QT_DEPRECATED_WARNINGS

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

HEADERS += cell.h \
           finddialog.h \
           gotocelldialog.h \
           mainwindow.h \
           sortdialog.h \
           spreadsheet.h
FORMS += gotocelldialog.ui sortdialog.ui
SOURCES += cell.cpp \
           finddialog.cpp \
           gotocelldialog.cpp \
           main.cpp \
           mainwindow.cpp \
           sortdialog.cpp \
           spreadsheet.cpp
