#include "worklogger_pres_model.h"
#include "worklogmodel_container.h"
#include "tablemodel.h"
#include <QSortFilterProxyModel>
#include <QRegExp>
#include <QString>
#include <functional>
#include <QSqlTableModel>
#include "mainwindow.h"
#include "dragdropmodel_factory.h"
#include "predestroy_signaller.h"

WorkLogger_Pres_Model::WorkLogger_Pres_Model(  StopWatch_Pres_Model *stopwatch_pres_model,
											   StopWatch_Model * stopwatch_model,
											   DropDownWidget *dropdown_projects,
											   DropDownWidget *dropdown_work_types,
											   QTextEdit *field_description,
											   QPushButton *btn_log_task,
											   QLabel *label_max_chars,
											   QObject *parent)
	  : Abstract_Pres_Model(parent),
		stopwatch_model(stopwatch_model),
		stopwatch_pres_model(stopwatch_pres_model),
		dropdown_projects(dropdown_projects),
		dropdown_work_types(dropdown_work_types),
		field_description(field_description),
		btn_log_task(btn_log_task),
		label_max_chars(label_max_chars),
		mapper(0)
{
	WorkLogModelContainer *wcp = WorkLogModelContainer::getSingleInstance();
	TableModel *worklogmodel = wcp->getModel();

	//hook up the UI elements as inputs to be inserted into Qt's hybrid business model/pres model;
	//the pres model is doing one of its job requirements here,
	//which is to connect UI interactions to the business model
	//TODO: recover this fxality
//	mapper = new SqlDataWidget_EntryMapper(worklogmodel, this);
//	mapper->addMapping(dropdown_work_types, 4, "sqlIndex");
//	mapper->addMapping(dropdown_projects, 5, "sqlIndex");
//	mapper->addMapping(field_description, worklogmodel->fieldIndex("description"), "plainText");
//	mapper->addMapping(stopwatch_model, worklogmodel->fieldIndex("start_time"), "startTime");
//	mapper->addMapping(stopwatch_model, worklogmodel->fieldIndex("end_time"), "endTime");
//	mapper->addMapping(stopwatch_model, worklogmodel->fieldIndex("task_duration"), "accruedTime");


	//TODO: have task btns' clicks trigger mapper.submit(),
	//      and thennn only have the stopwatch stop upon dataInserted("success")
	connect(stopwatch_model, SIGNAL(stopped()), mapper, SLOT(submit()));


	connect(mapper, &SqlDataWidget_EntryMapper::dataInserted,
			std::bind( &Abstract_Pres_Model::processEvent, this, "dataInserted" ));


//	//-----begin btn_play enabled behavior changes
	connect(field_description, &QTextEdit::textChanged,
			std::bind( &Abstract_Pres_Model::processEvent, stopwatch_pres_model, "description_textChanged" ));

	stopwatch_pres_model->addPropertyGoal("description_textChanged", stopwatch_pres_model->btn_play, "enabled", true);

	stopwatch_pres_model->addPropValRule(stopwatch_pres_model->btn_play, "enabled", true,
										 QPropRule(field_description, "plainText", QString())
										    );

	stopwatch_pres_model->addPropertyGoal("description_textChanged", stopwatch_pres_model->btn_play, "enabled", false);

	stopwatch_pres_model->addPropValRule(stopwatch_pres_model->btn_play, "enabled", false,
										 QPropRule(field_description, "plainText", QString(), PassTest,
												 	 	 	 RuleQualifier(RuleQual, "description_textChanged")
													 	 		)
										    	);

	stopwatch_pres_model->addPropertyGoal("stopped", stopwatch_pres_model->btn_play, "enabled", false);
//	//-----END btn_play enabled behavior changes


	connect(field_description, &QTextEdit::textChanged, this, &WorkLogger_Pres_Model::checkMaxChars);

	/* could not use pres model framework here because I want to test against a property of a property
	 * (the size of the plainText(QString) property of 'field_description',
	 * which currently is not within pres model's capabilities.
	 */


	addPropertyGoal("dataInserted", field_description, "plainText", QString());


	//TODO: recover this fxality
//	//------hook up work type and project models into dropdown views
//	QSqlTableModel* model_projects = DragDropModel_Factory::load("projects", true /*filter out 'is_delete'*/);
//	QSqlTableModel* model_worktypes = DragDropModel_Factory::load("work_types", true);
//
//	QSortFilterProxyModel *proxyModel_worktypes = new QSortFilterProxyModel(this);
//    proxyModel_worktypes->setSourceModel(model_worktypes);
//	proxyModel_worktypes->setFilterRegExp(QRegExp("T", Qt::CaseInsensitive));
//	proxyModel_worktypes->setFilterKeyColumn(model_worktypes->fieldIndex("is_active"));
//	QSortFilterProxyModel *proxyModel_projects = new QSortFilterProxyModel(this);
//    proxyModel_projects->setSourceModel(model_projects);
//	proxyModel_projects->setFilterRegExp(QRegExp("T", Qt::CaseInsensitive));
//	proxyModel_projects->setFilterKeyColumn(model_projects->fieldIndex("is_active"));
//
//	dropdown_work_types->setModel(proxyModel_worktypes);
//	dropdown_work_types->setModelColumn(model_worktypes->fieldIndex("work_type_title"));
//
//	dropdown_projects->setModel(proxyModel_projects);
//	dropdown_projects->setModelColumn(model_projects->fieldIndex("project_title"));

	//------END hook up work type and project models


	connect(btn_log_task, SIGNAL(clicked()), stopwatch_model, SLOT(stop()));


	connect(PreDestroy_Signaller::getSingleInstance(), &PreDestroy_Signaller::preDestroyed,
			this, &WorkLogger_Pres_Model::submitUnfinishedTask);
}

DropDownWidget* WorkLogger_Pres_Model::get_dropdown_work_types() {
	return dropdown_work_types;
}

DropDownWidget* WorkLogger_Pres_Model::get_dropdown_projects() {
	return dropdown_projects;
}

void WorkLogger_Pres_Model::checkMaxChars() {

	int charCount = field_description->toPlainText().size();
	if(charCount > 255) {
		label_max_chars->setProperty("visible", true);
		btn_log_task->setProperty("enabled", false);
		return;
	}
	if(charCount <= 255) {
		label_max_chars->setProperty("visible", false);
		btn_log_task->setProperty("enabled", true);
		return;
	}
}

void WorkLogger_Pres_Model::submitUnfinishedTask() {
	if(stopwatch_model->property("accruedTime") != QTime(0,0,0))
		stopwatch_model->stop();
		//this leads to a mapper->submit()/db insertion of task
}
