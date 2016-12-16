#include "worklogger_widget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSizePolicy>
#include <Qt>
#include <memory>

WorkLogger_Widget::WorkLogger_Widget(QWidget *parent)
	: QWidget(parent),
	  box_dropdown_projects(0),
	  box_dropdown_work_types(0),
	  dropdown_projects(0),
	  dropdown_work_types(0),
	  stopwatchwidget(0),
	  box_field_description(0),
	  field_description(0),
	  btn_log_task(0),
	  pres_model(0)
{
	QVBoxLayout *layout_1 = new QVBoxLayout();
	QHBoxLayout *layout_2 = new QHBoxLayout();
	layout_1->addLayout(layout_2);
	QVBoxLayout *layout_3 = new QVBoxLayout();
	layout_2->addLayout(layout_3);
	
	box_dropdown_projects = new QGroupBox(tr("Project:"));
	box_dropdown_work_types = new QGroupBox(tr("Work Category:"));
	layout_3->addWidget(box_dropdown_projects);
	layout_3->addWidget(box_dropdown_work_types);
	QVBoxLayout *layout_4 = new QVBoxLayout();
	QVBoxLayout *layout_5 = new QVBoxLayout();
	box_dropdown_projects->setLayout(layout_4);
	box_dropdown_work_types->setLayout(layout_5);
	dropdown_projects = new DropDownWidget();
	dropdown_work_types = new DropDownWidget();	
	layout_4->addWidget(dropdown_projects);
	layout_5->addWidget(dropdown_work_types);
	
	stopwatchwidget = new StopWatchWidget();
    layout_2->addWidget(stopwatchwidget);
	
	box_field_description = new QGroupBox(tr("Description:"));
	layout_1->addWidget(box_field_description);
	QVBoxLayout *layout_6 = new QVBoxLayout();
	box_field_description->setLayout(layout_6);
	field_description = new QTextEdit();
	layout_6->addWidget(field_description);
	
	btn_log_task = new QPushButton(tr("Log Task"));
	label_max_chars = new QLabel(tr("You are over the limit of characters allowed in the description."));
	label_max_chars->setProperty("visible", false);
	layout_1->addWidget(btn_log_task);
	layout_1->addWidget(label_max_chars);

	setLayout(layout_1);
	

	//----- secondary, cosmetic changes
	box_dropdown_projects->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	box_dropdown_work_types->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	field_description->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	layout_1->setAlignment(Qt::AlignTop);

	label_max_chars->setStyleSheet("QLabel { color : #c11515; }");

	pres_model = new WorkLogger_Pres_Model(
		stopwatchwidget->get_pres_model(),
		stopwatchwidget->get_dom_model(),
		dropdown_projects,
		dropdown_work_types,
		field_description,
		btn_log_task,
		label_max_chars,
		this
	);

}

WorkLogger_Pres_Model * WorkLogger_Widget::get_pres_model() {
	return pres_model;
}
