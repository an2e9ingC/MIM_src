#-------------------------------------------------
#
# Project created by QtCreator 2017-05-08T17:19:03
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MIM_Client
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    ../../Server/MIM_Server/mim_sc_common.h

FORMS    += mainwindow.ui
