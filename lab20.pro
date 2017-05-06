#-------------------------------------------------
#
# Project created by QtCreator 2015-02-04T13:43:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lab20
TEMPLATE = app


SOURCES += main.cpp\
        window.cpp \
    controller.cpp \
    model.cpp \
    pixel.cpp \
    scribblearea.cpp \
    sendreceive.cpp

HEADERS  += window.h \
    controller.h \
    model.h \
    pixel.h \
    scribblearea.h \
    sendreceive.h \
    serializable.h \
    common.h

CONFIG  += c++11

FORMS    += window.ui

LIBS += -L/usr/local/lib -lwiringPi -lpthread
