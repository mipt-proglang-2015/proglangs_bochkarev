#-------------------------------------------------
#
# Project created by QtCreator 2015-10-04T15:17:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Excel
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tableviewmodel.cpp \
    celldata.cpp

HEADERS  += mainwindow.h \
    tableviewmodel.h \
    celldata.h

FORMS    += mainwindow.ui
