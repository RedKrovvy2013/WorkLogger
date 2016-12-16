#ifndef WORKLOGGER_WIDGET_H
#define WORKLOGGER_WIDGET_H

#include <QWidget>
#include "dropdown_widget.h"
#include "stopwatchwidget.h"
#include <QPushButton>
#include <QGroupBox>
#include <QTextEdit>
#include <QLabel>
#include "worklogger_pres_model.h"

class WorkLogger_Widget : public QWidget
{
	Q_OBJECT
public:
    explicit WorkLogger_Widget(QWidget *parent = 0);
    WorkLogger_Pres_Model *get_pres_model();

private:
    QGroupBox *box_dropdown_projects;
    QGroupBox *box_dropdown_work_types;
    DropDownWidget *dropdown_projects;
    DropDownWidget *dropdown_work_types; 
    StopWatchWidget *stopwatchwidget;
    QGroupBox *box_field_description;
    QTextEdit *field_description;
    QPushButton *btn_log_task;
    QLabel *label_max_chars;
    
    WorkLogger_Pres_Model *pres_model;
};

#endif // WORKLOGGER_WIDGET_H
