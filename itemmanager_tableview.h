#ifndef ITEMMANAGER_TABLEVIEW_H
#define ITEMMANAGER_TABLEVIEW_H

#include <QObject>
#include <QWidget>
#include <QContextMenuEvent>
#include <QAction>
#include <QTableView>
#include <QString>
#include "dragdrop_sqltablemodel.h"

class ItemManager_TableView : public QTableView
{
	Q_OBJECT
public:
    explicit ItemManager_TableView(QString tablename, QWidget * parent = 0);

protected:
    void contextMenuEvent(QContextMenuEvent *event) Q_DECL_OVERRIDE;

private:
    DragDrop_SqlTableModel* no_is_deleted_model;
    DragDrop_SqlTableModel* fullModel;
    QAction *deleteAct;

private slots:
	void deleteItem();
};

#endif // ITEMMANAGER_TABLEVIEW_H
