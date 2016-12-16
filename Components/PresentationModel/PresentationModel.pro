#-------------------------------------------------
#
# Project created by QtCreator 2016-12-15T16:19:02
#
#-------------------------------------------------

QT       += widgets

QT       -= gui

TARGET = PresentationModel
TEMPLATE = lib
CONFIG += staticlib

SOURCES += abstract_pres_model.cpp

HEADERS += abstract_pres_model.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
