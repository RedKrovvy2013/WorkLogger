#-------------------------------------------------
#
# Project created by QtCreator 2015-09-28T13:19:31
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = work_logger
TEMPLATE = app

QTPLUGIN += QSQLMYSQL

INCLUDEPATH += "C:\Users\RedKrovvy\code\C++\Qt\include" "C:\Users\RedKrovvy\code\C++\include"

SOURCES += main.cpp\
           mainwindow.cpp \
    	   db_container.cpp \
    	   dropdown_widget.cpp \
    	   worklogviewer_widget.cpp \
    	   sqldatawidget_entrymapper.cpp \
    worklogger_widget.cpp \
    stopwatchwidget.cpp \
    mainwidget.cpp \
    worklogmodel_container.cpp \
    timeformatdelegate.cpp \
    item_manager_dialog.cpp \
    btn_and_lineedit_widget.cpp \
    abstract_resettable_widget.cpp \
    dragdrop_sqltablemodel.cpp \
    worklogger_pres_model.cpp \
    stopwatch_pres_model.cpp \
    stopwatch_model.cpp \
    abstract_pres_model.cpp \
    worktypes_model_container.cpp \
    dragdropmodel_factory.cpp \
    itemmanager_tableview.cpp \
    dbthreadmanager.cpp \
    tablemodel.cpp \
    dbtalker.cpp

HEADERS  += mainwindow.h \
    		db_container.h \
    		dropdown_widget.h \
    		worklogviewer_widget.h \
    		sqldatawidget_entrymapper.h \
    worklogger_widget.h \
    stopwatchwidget.h \
    mainwidget.h \
    worklogmodel_container.h \
    widgets_utility.h \
    timeformatdelegate.h \
    item_manager_dialog.h \
    btn_and_lineedit_widget.h \
    abstract_resettable_widget.h \
    dragdrop_sqltablemodel.h \
    worklogger_pres_model.h \
    stopwatch_pres_model.h \
    stopwatch_model.h \
    abstract_pres_model.h \
    worktypes_model_container.h \
    dragdropmodel_factory.h \
    itemmanager_tableview.h \
    dbthreadmanager.h \
    tablemodel.h \
    dbtalker.h

unix {
	target.path = /usr/local/bin/
	INSTALLS += target
}