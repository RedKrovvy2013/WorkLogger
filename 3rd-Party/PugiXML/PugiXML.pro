#-------------------------------------------------
#
# Project created by QtCreator 2016-08-02T15:46:19
#
#-------------------------------------------------

QT       -= core gui

TARGET = PugiXML
TEMPLATE = lib
CONFIG += staticlib

SOURCES += pugixml.cpp

HEADERS += pugixml.hpp

unix {
    target.path = /usr/lib
    INSTALLS += target
}
