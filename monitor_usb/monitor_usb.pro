#-------------------------------------------------
#
# Project created by QtCreator 2017-02-14T22:25:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = monitor_usb
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    mythread.h \
    mysdc.h

FORMS    += mainwindow.ui
