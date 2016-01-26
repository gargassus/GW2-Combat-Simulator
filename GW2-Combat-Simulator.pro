#-------------------------------------------------
#
# Project created by QtCreator 2016-01-19T16:52:30
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gw
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    comminterfacejson.cpp

HEADERS  += mainwindow.h \
    comminterfacejson.h

FORMS    += mainwindow.ui
