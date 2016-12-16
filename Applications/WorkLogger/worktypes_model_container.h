#ifndef WORKTYPES_MODEL_CONTAINER_H
#define WORKTYPES_MODEL_CONTAINER_H

#include <QObject>
#include "dragdrop_sqltablemodel.h"

class WorkTypes_Model_Container : public QObject
{
    Q_OBJECT
public:
	static DragDrop_SqlTableModel* getSingleInstance();

private:
    explicit WorkTypes_Model_Container(QObject *parent = 0);
    DragDrop_SqlTableModel* model;
};

#endif // WORKTYPES_MODEL_CONTAINER_H
