#include "dragdropmodel_factory.h"
#include "db_container.h"

DragDropModel_Factory::DragDropModel_Factory(QObject *parent) : QObject(parent) {

}

DragDrop_SqlTableModel* DragDropModel_Factory::load(QString tableName, bool isFilter) {

	if(isFilter) {

		if(models.contains(tableName)) {

			models[tableName]->select();
			return models[tableName];
		} else {

			static DbContainer *dbContainer = DbContainer::getSingleInstance();
			DragDrop_SqlTableModel* model
				= new DragDrop_SqlTableModel(dbContainer->getDb());
			model->setTable(tableName);
			model->setEditStrategy(QSqlTableModel::OnManualSubmit);
			model->setFilter("is_deleted != 'T'");
			model->select();

			models[tableName] = model;
			return model;
		}
	} else {

		if(fullModels.contains(tableName)) {

			fullModels[tableName]->select();
			return fullModels[tableName];
		} else {

			static DbContainer *dbContainer = DbContainer::getSingleInstance();
			DragDrop_SqlTableModel* model
				= new DragDrop_SqlTableModel(dbContainer->getDb());
			model->setTable(tableName);
			model->setEditStrategy(QSqlTableModel::OnManualSubmit);
			model->select();

			fullModels[tableName] = model;
			return model;
		}
	}
}

QMap<QString, DragDrop_SqlTableModel*> DragDropModel_Factory::models
	= QMap<QString, DragDrop_SqlTableModel*>();

QMap<QString, DragDrop_SqlTableModel*> DragDropModel_Factory::fullModels
	= QMap<QString, DragDrop_SqlTableModel*>();
