#ifndef WORKLOGMODEL_H
#define WORKLOGMODEL_H

#include <QObject>
#include "concurrentdbtablemodel.h"

class WorkLogModelContainer : public QObject
{
    Q_OBJECT
public:
    static WorkLogModelContainer * getSingleInstance();
    ConcurrentDBTableModel * getModel();
private:
    explicit WorkLogModelContainer(QObject *parent = 0);
    ConcurrentDBTableModel *model;
};

#endif // WORKLOGMODEL_H
