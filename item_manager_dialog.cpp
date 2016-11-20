#include "item_manager_dialog.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QRegExp>
#include <functional>
#include <QAbstractItemView>
#include <QHeaderView>
#include <QDate>
#include "dragdropmodel_factory.h"
#include <QDebug>
#include <QModelIndex>
#include <QGroupBox>

#include "db_container.h"

ItemManagerDialog::ItemManagerDialog(QString tableName, QWidget* parent)
	: QDialog(parent),
	  proxyModel_active(0),
	  proxyModel_inactive(0),
	  activeView(0),
	  inactiveView(0),
	  add_item_widget(0)
{
	if(tableName=="projects") {
		setWindowTitle(tr("Projects Manager"));
	} else {
		setWindowTitle(tr("Work Categories Manager"));
	}

	model = DragDropModel_Factory::load(tableName, true /*filter out 'is_delete'*/);
	fullModel = DragDropModel_Factory::load(tableName, false);

	proxyModel_active = new QSortFilterProxyModel(this);
    proxyModel_active->setSourceModel(model);
	proxyModel_active->setFilterRegExp(QRegExp("T", Qt::CaseInsensitive));
	proxyModel_active->setFilterKeyColumn(model->fieldIndex("is_active"));

	proxyModel_inactive = new QSortFilterProxyModel(this);
    proxyModel_inactive->setSourceModel(model);
	proxyModel_inactive->setFilterRegExp(QRegExp("F", Qt::CaseInsensitive));
	proxyModel_inactive->setFilterKeyColumn(model->fieldIndex("is_active"));

	activeView = new ItemManager_TableView(tableName, this);
	activeView->setModel(proxyModel_active);
    activeView->hideColumn(0);
    activeView->hideColumn(2);
	activeView->hideColumn(3);
	activeView->hideColumn(4);
	activeView->hideColumn(5);
    activeView->setDragEnabled(true);
	activeView->setAcceptDrops(true);
	activeView->setDropIndicatorShown(true);
	activeView->verticalHeader()->hide();

	inactiveView = new ItemManager_TableView(tableName, this);
	inactiveView->setModel(proxyModel_inactive);
	inactiveView->hideColumn(0);
	inactiveView->hideColumn(2);
	inactiveView->hideColumn(3);
	inactiveView->hideColumn(4);
	inactiveView->hideColumn(5);
	inactiveView->setDragEnabled(true);
	inactiveView->setAcceptDrops(true);
	inactiveView->setDropIndicatorShown(true);
	inactiveView->verticalHeader()->hide();
	
	QHBoxLayout * layout_1 = new QHBoxLayout();
	QVBoxLayout * layout_2 = new QVBoxLayout();
	QVBoxLayout * layout_3 = new QVBoxLayout();
	QGroupBox* box_active = new QGroupBox("Active");
	QGroupBox* box_inactive = new QGroupBox("Inactive");
	
	layout_1->addWidget(box_active);
	layout_1->addWidget(box_inactive);
	box_active->setLayout(layout_2);
	box_inactive->setLayout(layout_3);

	layout_3->addWidget(inactiveView);
	layout_2->addWidget(activeView);
	
	add_item_widget = new Btn_And_LineEdit_Widget(this);
	layout_2->addWidget(add_item_widget);
	
	setLayout(layout_1);

	//--- and finally plug in the data entry mapping for the new item QLineEdit,
	//    now that the widgets have been constructed
//    mapper = new SqlDataWidget_EntryMapper(model.get(), this);
    mapper = new SqlDataWidget_EntryMapper(model, this);
	//keep the '1' here; the work_types and projects table both have
	//their title fields in col 1
	mapper->addMapping(add_item_widget, 1, "text");
	mapper->addMapping(model->fieldIndex("is_active"), "T");
	mapper->addMapping(model->fieldIndex("is_deleted"), "F");

    if(tableName=="projects") {
		mapper->addMapping(model->fieldIndex("is_archived"), "F");
		mapper->addMapping(model->fieldIndex("start_date"),
						   QDate::currentDate().toString("yyyy-MM-dd"));
	}

//	connect(add_item_widget, SIGNAL(btn_clicked()), mapper, SLOT(submit()));
    connect(add_item_widget, SIGNAL(btn_clicked()), this, SLOT(preSubmit()));
	connect(add_item_widget, &Btn_And_LineEdit_Widget::btn_clicked,
			std::bind(&Btn_And_LineEdit_Widget::reset, add_item_widget, "default"));

	//----cosmetics:
	model->setHeaderData(1, Qt::Horizontal, tr(""));
}

void ItemManagerDialog::preSubmit() {

    for(int i=0; i<fullModel->rowCount(); ++i) {

        QModelIndex qi
            = fullModel->index(i, fullModel->fieldIndex("work_type_title"));

        if(fullModel->data(qi).toString()==add_item_widget->property("text")) {

            QModelIndex qi
                = fullModel->index(i, fullModel->fieldIndex("is_deleted"));
            if(fullModel->data(qi).toString()=="T") {

                fullModel->setData(qi, "F");
                model->submitAll();
                //TODO: make note on bug that model->submitAll() resolves
                fullModel->submitAll();
                model->select(); //need to update 'model' here
                fullModel->select();  //TODO: might not need to update fullModel here..
            }
            return;//if 'is_deleted'=='F', do nothing
        }
    }

    //if we get here, 'itemTitle' does not exist in fullModel,
    //so add it.
    mapper->submit();
    fullModel->select();
    //--avoids bug of:
    //      1) inserting new item,
    //      2) preSubmit()ing item with same title
    //      3) and having same-titled item inserted
    //         because fullModel didn't know of it
    //         because it wasn't select()'d after
    //         step (1) insertion
}

int ItemManagerDialog::exec() {

	int ret = QDialog::exec();
	model->submitAll();
	model->select();
	/*
	 * avoids this bug:
	 * 	   1) switch some inactive/actives
	 * 	   2) close program, re-open program
	 * 	   3) step 1 switches have not persisted
	 */
	return ret;
}
