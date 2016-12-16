#include "itemmanager_tableview.h"
#include <QMenu>
#include <QSortFilterProxyModel>
#include <QSqlTableModel>
#include "dragdropmodel_factory.h"

ItemManager_TableView::ItemManager_TableView(QString tableName, QWidget * parent)
	: QTableView(parent)
{
	no_is_deleted_model = DragDropModel_Factory::load(tableName, true);
	fullModel = DragDropModel_Factory::load(tableName, false);

	deleteAct = new QAction(tr("Delete"), this);
	deleteAct->setShortcuts(QKeySequence::Delete);
	connect(deleteAct, &QAction::triggered, this, &ItemManager_TableView::deleteItem);
}

void ItemManager_TableView::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    menu.addAction(deleteAct);
    menu.exec(event->globalPos());
}

void ItemManager_TableView::deleteItem()
{
	QSortFilterProxyModel* proxyModel = (QSortFilterProxyModel*)model();
//	QSqlTableModel* model = (QSqlTableModel*)proxyModel->sourceModel();
	QModelIndex i = no_is_deleted_model->index(
		proxyModel->mapToSource(selectionModel()->currentIndex()).row(),
								no_is_deleted_model->fieldIndex("is_deleted"));
	no_is_deleted_model->setData(i, "T");
	no_is_deleted_model->submitAll();
	no_is_deleted_model->select();
	fullModel->select();
	/*having fullModel->select() here resolves this bug:
	 *    1) ui-delete item
	 *    2) ui-adding back same-titled item does not work
	 */
}
