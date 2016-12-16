#-------------------------------------------------
#
# Project created by QtCreator 2016-12-15T16:19:02
#
#-------------------------------------------------

QT       += widgets sql

QT       -= gui

TARGET = SqlDataWidget_EntryMapper
TEMPLATE = lib
CONFIG += staticlib

SOURCES += sqldatawidget_entrymapper.cpp

HEADERS += sqldatawidget_entrymapper.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
