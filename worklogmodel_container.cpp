#include "worklogmodel_container.h"
#include "db_container.h"

#include <QModelIndex>

WorkLogModelContainer::WorkLogModelContainer(QObject *parent) : QObject(parent)
{
	model = new TableModel(this);

//	DbContainer *dbContainer = DbContainer::getSingleInstance();
//	model = new QSqlRelationalTableModel(this, dbContainer->getDb());
//	model->setTable("tasks");
//	model->setEditStrategy(QSqlTableModel::OnManualSubmit);
//
//	model->setHeaderData(1, Qt::Horizontal, tr("Start Time"));
//	model->setHeaderData(2, Qt::Horizontal, tr("End Time"));
//	model->setHeaderData(3, Qt::Horizontal, tr("Task Duration"));
//	model->setHeaderData(4, Qt::Horizontal, tr("Work Category"));
//	model->setHeaderData(5, Qt::Horizontal, tr("Project"));
//	model->setHeaderData(6, Qt::Horizontal, tr("Description"));
//
//	model->setRelation(model->fieldIndex("work_type_id"), QSqlRelation("work_types", "work_type_id", "work_type_title"));
//	model->setRelation(model->fieldIndex("project_id"), QSqlRelation("projects", "project_id", "project_title"));
//	//note!--->model->select() must come after these relation settings for them to take effect
//
//    //model->setSort(model->fieldIndex("start_time"), Qt::DescendingOrder);
//
//	/* 'model->select()' Populates the model with data from the table that was set via setTable(),
//	 * using the specified filter and sort condition, and returns
//	 * true if successful; otherwise returns false. */
//	model->select();
}

WorkLogModelContainer * WorkLogModelContainer::getSingleInstance() {
	static WorkLogModelContainer *wcp = new WorkLogModelContainer();
	return wcp;
}

TableModel * WorkLogModelContainer::getModel() {
	return model;
}
