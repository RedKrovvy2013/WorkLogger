#ifndef WORKLOGGER_PRES_MODEL_H
#define WORKLOGGER_PRES_MODEL_H

#include <QObject>
#include "dropdown_widget.h"
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include <memory>
#include "abstract_pres_model.h"
#include "stopwatch_pres_model.h"
#include "stopwatch_model.h"
#include "sqldatawidget_entrymapper.h"
#include "dragdrop_sqltablemodel.h"

class WorkLogger_Pres_Model : public Abstract_Pres_Model
{
	Q_OBJECT
public:
    WorkLogger_Pres_Model( StopWatch_Pres_Model *,
    		               StopWatch_Model *,
    					   DropDownWidget *,
						   DropDownWidget *,
						   QTextEdit *,
						   QPushButton *,
						   QLabel *,
						   QObject *parent = 0);

	DropDownWidget* get_dropdown_work_types();
	DropDownWidget* get_dropdown_projects();

private:
	StopWatch_Pres_Model *stopwatch_pres_model;
	StopWatch_Model * stopwatch_model;
	std::unique_ptr<DragDrop_SqlTableModel> model_projects;
	std::unique_ptr<DragDrop_SqlTableModel> model_worktypes;
    DropDownWidget * dropdown_projects;
	DropDownWidget * dropdown_work_types;
	QTextEdit * field_description;
	int field_description_count;
	QPushButton * btn_log_task;
	QLabel * label_max_chars;
    SqlDataWidget_EntryMapper * mapper;

private slots:
    void checkMaxChars();
    void submitUnfinishedTask();
};

#endif // WORKLOGGER_PRES_MODEL_H
