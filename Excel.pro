#-------------------------------------------------
#
# Project created by QtCreator 2015-10-04T15:17:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Excel
TEMPLATE = app

# PYTHON
CONFIG += no_keywords # Python redefines some qt keywords
INCLUDEPATH += /usr/include/python2.7
LIBS += -lpython2.7

CONFIG += c++11

SOURCES += main.cpp\
    TableViewModel.cpp \
    MainWindow.cpp \
    PythonInterpreter.cpp

HEADERS  += \
    CellData.h \
    MainWindow.h \
    TableViewModel.h \
    PythonInterpreter.h \
    common.h

FORMS    += \
    MainWindow.ui

RESOURCES += \
    Resources.qrc
