#-------------------------------------------------
#
# Project created by QtCreator 2015-12-14T05:27:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Excel
TEMPLATE = app

# PYTHON
CONFIG += no_keywords console  # Python redefines some qt keywords
INCLUDEPATH += /usr/include/python3.4m
LIBS += -lpython3.4m -lpthread -ldl -lutil -lm -Xlinker -export-dynamic

CONFIG += c++11

SOURCES += main.cpp \
    InterpreterHandler.cpp \
    MainWindow.cpp \
    PythonInterpreter.cpp \
    TableViewController.cpp

HEADERS  += \
    CellData.h \
    InterpreterHandler.h \
    MainWindow.h \
    PythonInterpreter.h \
    TableViewController.h \
    Exception.h

FORMS    += \
    MainWindow.ui

RESOURCES += \
    Resources.qrc
