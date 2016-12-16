#-------------------------------------------------
#
# Project created by QtCreator 2016-12-15T16:23:33
#
#-------------------------------------------------

QT       -= gui

TARGET = PreDestroy
TEMPLATE = lib
CONFIG += staticlib

SOURCES += predestroy_guard.cpp \
           predestroy_signaller.cpp

HEADERS += predestroy_signaller.h \
           predestroy_guard.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
