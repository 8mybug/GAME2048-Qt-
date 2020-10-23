#-------------------------------------------------
#
# Project created by QtCreator 2020-10-16T16:21:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Game2048
TEMPLATE = app


SOURCES += main.cpp\
        widget2048.cpp \
    label.cpp

HEADERS  += widget2048.h \
    label.h

FORMS    += widget2048.ui
