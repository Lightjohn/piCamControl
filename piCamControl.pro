#-------------------------------------------------
#
# Project created by QtCreator 2014-11-29T16:11:40
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = piCamControl
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    network.cpp

HEADERS  += mainwindow.h \
    network.h

FORMS    += mainwindow.ui
