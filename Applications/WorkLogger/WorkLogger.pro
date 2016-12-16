#-------------------------------------------------
#
# Project created by QtCreator 2016-12-15T16:20:21
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WorkLogger
TEMPLATE = app

INCLUDEPATH += ../../Components/PresentationModel \
               ../../Components/PreDestroy \
               ../../Components/SqlDataWidget_EntryMapper \
               ../../3rd-Party/PugiXML

LIBS += ../../3rd-Party/PugiXML/debug/PugiXML.lib \
        ../../Components/PresentationModel/debug/PresentationModel.lib \
        ../../Components/PreDestroy/debug/PreDestroy.lib \
        ../../Components/SqlDataWidget_EntryMapper/debug/SqlDataWidget_EntryMapper.lib

SOURCES +=  main.cpp\
            mainwindow.cpp \
            db_container.cpp \
            dropdown_widget.cpp \
            worklogviewer_widget.cpp \
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
            worktypes_model_container.cpp \
            dragdropmodel_factory.cpp \
            itemmanager_tableview.cpp \
            descriptiondelegate.cpp

HEADERS  += mainwindow.h \
            db_container.h \
            dropdown_widget.h \
            worklogviewer_widget.h \
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
            worktypes_model_container.h \
            dragdropmodel_factory.h \
            itemmanager_tableview.h \
            descriptiondelegate.h

unix {
    target.path = /usr/local/bin/
    INSTALLS += target
}
