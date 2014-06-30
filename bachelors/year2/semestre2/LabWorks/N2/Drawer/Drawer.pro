#-------------------------------------------------
#
# Project created by QtCreator 2014-03-22T16:36:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Drawer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    pane.cpp \
    serverpane.cpp \
    clientpane.cpp \
    mysocket.cpp \
    datahandler.cpp

HEADERS  += mainwindow.h \
    pane.h \
    serverpane.h \
    clientpane.h \
    mysocket.h \
    datahandler.h

FORMS    += mainwindow.ui

CONFIG += c++11

LIBS += -lws2_32
LIBS += -lmswsock
LIBS += -ladvapi32
