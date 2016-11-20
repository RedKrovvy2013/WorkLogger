#include "sqldatawidget_entrymapper.h"
#include <QModelIndex>
#include <Qt>
#include <QDebug>
#include <QSqlError>
#include <QDateTime>

SqlDataWidget_EntryMapper::SqlDataWidget_EntryMapper(QSqlTableModel *model, QObject *parent)
	: QObject(parent), model(model) {
	connect( model, SIGNAL(destroyed()), this, SLOT(modelDestroyed()) );
}

void SqlDataWidget_EntryMapper::addMapping(QObject *object, const int column, const QByteArray &property) {
	std::shared_ptr<DataWidgetEntryItem> widgetData(new DataWidgetEntryItem(object, column, property));
	entryMap.append(PreEntryItem(widgetData, std::shared_ptr<ManualEntryItem>(), true /* isWidgetEntry */));
}

void SqlDataWidget_EntryMapper::addMapping(const int column, const QVariant& value) {
	std::shared_ptr<ManualEntryItem> manualData(new ManualEntryItem(column, value));
	entryMap.append(PreEntryItem(std::shared_ptr<DataWidgetEntryItem>(), manualData, false /* isWidgetEntry */));
}

bool SqlDataWidget_EntryMapper::submit() {
	if(!model) {
		qDebug() << "The model attached to this SqlDataWidget_EntryMapper has been destroyed."
				    "It cannot submit its data.";
		return false;
	}
		
	//QSqlTableModel's impl of the fx below takes care of beginInsertRows()/endInsertRows()
	//needed for notifying connected views of change
	model->insertRow(0, QModelIndex());
	//docu says that insertRow:param-1 is row to insert before,
	//but in testing, using 0 as param magically appends data to db :)
	
	QList<PreEntryItem>::const_iterator it = entryMap.cbegin();
	QList<PreEntryItem>::const_iterator end = entryMap.cend();
	while(it!=end) {
		bool isSubmitHelper;
		if(it->isWidgetEntry_) {
			isSubmitHelper = submit_helper(
								 it->data_item_p_->column_,
						   	 	 it->data_item_p_->object_->property(it->data_item_p_->property_)
								 	 	 	);
			if(!isSubmitHelper)
				return false;
		} else {
			isSubmitHelper = submit_helper(
							 	 it->manual_item_p_->column_,
								 it->manual_item_p_->value_
								 	 	 	);
			if(!isSubmitHelper)
				return false;
		} 
		++it;
	}
	
	if(!model->submitAll()) {
		qDebug() << model->lastError();
		return false;
	}

	emit(dataInserted());
	return true;
}

bool SqlDataWidget_EntryMapper::submit_helper(int column, const QVariant& val) {
	QModelIndex i = model->index(0, column, QModelIndex());
	if( !( model->setData(i, val) ) ) {
		qDebug() << "The data for column " << column << " could not be set.";
		return false;
	}
	return true;
}

QSqlTableModel * SqlDataWidget_EntryMapper::getModel() const {
	return model;
}

void SqlDataWidget_EntryMapper::modelDestroyed() {	model = 0; }
