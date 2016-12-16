#include "dropdown_widget.h"
#include <QAbstractItemModel>
#include <QModelIndex>

DropDownWidget::DropDownWidget(QWidget *parent)
	: QComboBox(parent) { }

int DropDownWidget::getSqlIndex() const {
	QAbstractItemModel *proxyModel = model();
	QModelIndex proxyIndex = proxyModel->index(property("currentIndex").toInt(), 0);
	//the '0' here is a hard-code; it also relies on any tables associated
	//with this widget to have its 'id' be in the first column
	//TODO: remove this hearh hard-codin'!
	return proxyModel->data(proxyIndex).toInt();
}
