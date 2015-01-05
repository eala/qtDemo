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
    sortdialog.cpp

HEADERS  +=\
        finddialog.h \
    gotocelldialog.h \
    sortdialog.h

FORMS    +=\
        finddialog.ui \
    gotocelldialog.ui \
    sortdialog.ui
