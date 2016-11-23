#include "worklogviewer_widget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSqlRelation>
#include <QSqlRelationalDelegate>
#include <QHeaderView>
#include "worklogmodel_container.h"
#include "timeformatdelegate.h"

WorkLogViewer_Widget::WorkLogViewer_Widget(QWidget *parent)
	: QWidget(parent),
	  box_worklogviewer(0),
	  view(0)
{		
	view = new QTableView(this);
	WorkLogModelContainer *wcp = WorkLogModelContainer::getSingleInstance();
	worklogmodel = wcp->getModel();
	view->setModel(worklogmodel);
//	If you use a read-write QSqlRelationalTableModel, you probably want to use QSqlRelationalDelegate on the view.
//	Unlike the default delegate, QSqlRelationalDelegate provides a combobox for fields that are foreign
//	keys into other tables. To use the class, simply call QAbstractItemView::setItemDelegate() on the view
//	with an instance of QSqlRelationalDelegate

	//TODO: recover this fxality
//	view->setItemDelegate(new QSqlRelationalDelegate(view));
//	view->hideColumn(0); // don't show the ID
	view->verticalHeader()->hide();
	view->setAlternatingRowColors(true);
	view->resizeColumnsToContents();
	
	QVBoxLayout *layout_1 = new QVBoxLayout();
	box_worklogviewer = new QGroupBox(tr("Work Log Viewer"));
	layout_1->addWidget(box_worklogviewer);
	QVBoxLayout *layout_2 = new QVBoxLayout();
	box_worklogviewer->setLayout(layout_2);

	QHBoxLayout *layout_3 = new QHBoxLayout();
	layout_2->addLayout(layout_3);
	line_edit_range_start = new QLineEdit("2016-02-01", this);
	line_edit_range_end = new QLineEdit("2016-04-01", this);
	btn_update_range = new QPushButton("Update Range");
	layout_3->addWidget(line_edit_range_start);
	layout_3->addWidget(line_edit_range_end);
	layout_3->addWidget(btn_update_range);

	layout_2->addWidget(view);

	setLayout(layout_1);
	

	//------ column formatting...
//	view->setItemDelegateForColumn(3, new TimeFormatDelegate("hh:mm:ss"));


	//------ setting up date range updater
	connect(btn_update_range, &QPushButton::clicked,
			this, &WorkLogViewer_Widget::updateRangeHandler);
}

void WorkLogViewer_Widget::updateRangeHandler() {
//TODO: recover this fxality
//	QString sqlClause("start_time > '");
//	sqlClause.append(line_edit_range_start->text());
//	sqlClause.append(" 00:00:00");
//	sqlClause.append("' AND start_time < '");
//	sqlClause.append(line_edit_range_end->text());
//	sqlClause.append(" 00:00:00");
//	sqlClause.append("'");
//	worklogmodel->setFilter(sqlClause);
//	worklogmodel->select();
}
//model->setFilter("start_time > '2016-02-01 00:00:00' AND start_time < '2016-04-01 00:00:00'");
