#ifndef WORKLOGMODEL_H
#define WORKLOGMODEL_H

#include <QObject>
#include <QSqlRelationalTableModel>

class WorkLogModelContainer : public QObject
{
    Q_OBJECT
public:
    static WorkLogModelContainer * getSingleInstance();
    QSqlRelationalTableModel * getModel();
//    ~WorkLogModelContainer();
private:
    explicit WorkLogModelContainer(QObject *parent = 0);
    QSqlRelationalTableModel *model;
};

#endif // WORKLOGMODEL_H
