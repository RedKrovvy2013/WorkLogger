#ifndef WORKLOGMODEL_H
#define WORKLOGMODEL_H

#include <QObject>
#include "tablemodel.h"

class WorkLogModelContainer : public QObject
{
    Q_OBJECT
public:
    static WorkLogModelContainer * getSingleInstance();
    TableModel * getModel();
private:
    explicit WorkLogModelContainer(QObject *parent = 0);
    TableModel *model;
};

#endif // WORKLOGMODEL_H
