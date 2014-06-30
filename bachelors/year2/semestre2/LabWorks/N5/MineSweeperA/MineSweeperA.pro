#-------------------------------------------------
#
# Project created by QtCreator 2014-03-02T13:48:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MineSweeperA
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    game.cpp

HEADERS  += mainwindow.h \
    game.h

FORMS    += mainwindow.ui

CONFIG += mobility
CONFIG += c++11
MOBILITY = 

RESOURCES += \
    rs.qrc

