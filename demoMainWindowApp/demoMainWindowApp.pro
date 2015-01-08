#-------------------------------------------------
#
# Project created by QtCreator 2015-01-05T21:34:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = demoMainWindowApp
TEMPLATE = app


SOURCES += main.cpp\
        finddialog.cpp \
    gotocelldialog.cpp \
    sortdialog.cpp \
    mainwindow.cpp \
    spreadsheet.cpp \
    spreadsheetcompare.cpp

HEADERS  +=\
        finddialog.h \
    gotocelldialog.h \
    sortdialog.h \
    mainwindow.h \
    spreadsheet.h \
    spreadsheetcompare.h

FORMS    +=\
        finddialog.ui \
    gotocelldialog.ui \
    sortdialog.ui

install_bin.path = $$OUT_PWD
install_bin.files = bin/images/*

INSTALLS += \
    install_bin

RESOURCES += \
    demomainwindow.qrc
