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
        mainwindow.cpp\
        finddialog.cpp \
    gotocelldialog.cpp

HEADERS  += mainwindow.h\
        finddialog.h \
    gotocelldialog.h

FORMS    += mainwindow.ui\
        finddialog.ui \
    gotocelldialog.ui
