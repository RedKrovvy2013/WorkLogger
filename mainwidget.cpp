#include "mainwidget.h"
#include <QHBoxLayout>

MainWidget::MainWidget(QWidget *parent) 
	: QWidget(parent),
	  worklogger_widget(0),
	  worklogviewer_widget(0)
{
	QHBoxLayout *layout_1 = new QHBoxLayout();
	worklogger_widget = new WorkLogger_Widget(this);
	worklogviewer_widget = new WorkLogViewer_Widget(this);
	layout_1->addWidget(worklogger_widget);
	layout_1->addWidget(worklogviewer_widget);
	setLayout(layout_1);
}

WorkLogger_Widget *MainWidget::get_worklogger_widget() {
	return worklogger_widget;
}
