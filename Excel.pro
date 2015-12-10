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
    TableViewModel.cpp \
    CellData.cpp \
    MainWindow.cpp

HEADERS  += \
    CellData.h \
    MainWindow.h \
    TableViewModel.h

FORMS    += \
    MainWindow.ui

RESOURCES += \
    Resources.qrc
