#ifndef ITEM_MANAGER_DIALOG_H_
#define ITEM_MANAGER_DIALOG_H_

#include <QDialog>
#include <QWidget>
#include <QString>
#include <QSortFilterProxyModel>
#include <QTableView>
#include <memory>
#include "sqldatawidget_entrymapper.h"
#include "btn_and_lineedit_widget.h"
#include "dragdrop_sqltablemodel.h"
#include "itemmanager_tableview.h"

class ItemManagerDialog : public QDialog {
	Q_OBJECT
	
public:
	ItemManagerDialog(QString, QWidget* parent = 0);
	int exec();
	
private:
    DragDrop_SqlTableModel* model;
    DragDrop_SqlTableModel* fullModel;
	QSortFilterProxyModel *proxyModel_active;
	QSortFilterProxyModel *proxyModel_inactive;

	SqlDataWidget_EntryMapper *mapper;
	
	ItemManager_TableView *activeView;
	ItemManager_TableView *inactiveView;
	Btn_And_LineEdit_Widget *add_item_widget;

private slots:
    void preSubmit();
};

#endif
