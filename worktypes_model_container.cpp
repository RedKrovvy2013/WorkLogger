#include "worktypes_model_container.h"
#include "db_container.h"

WorkTypes_Model_Container::WorkTypes_Model_Container(QObject *parent) : QObject(parent)
{
	DbContainer *dbContainer = DbContainer::getSingleInstance();
	model = new DragDrop_SqlTableModel(dbContainer->getDb(), this);
	model->setTable("work_types");
	model->setEditStrategy(QSqlTableModel::OnManualSubmit);
	model->select();
}

DragDrop_SqlTableModel* WorkTypes_Model_Container::getSingleInstance() {
	static WorkTypes_Model_Container* wcp = new WorkTypes_Model_Container();
	return wcp->model;
}
