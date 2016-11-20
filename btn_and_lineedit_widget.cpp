#include "btn_and_lineedit_widget.h"
#include <QHBoxLayout>

//foo

Btn_And_LineEdit_Widget::Btn_And_LineEdit_Widget(QWidget *parent)
    : AbstractResettableWidget(parent),
	  btn(0),
	  lineEdit(0)
{
	btn = new QPushButton("Add", this);
	lineEdit = new QLineEdit(this);

	QHBoxLayout * layout = new QHBoxLayout();
	layout->addWidget(btn);
	layout->addWidget(lineEdit);

	setLayout(layout);

	std::shared_ptr<WidgetResetItem> reset_item_1(new WidgetResetItem(lineEdit, "text", QString()));
	resets["default"].push_back(reset_item_1);

	connect(btn, SIGNAL(clicked()), this, SIGNAL(btn_clicked()));
}

QString Btn_And_LineEdit_Widget::getText() const {
	return lineEdit->property("text").toString();
}
