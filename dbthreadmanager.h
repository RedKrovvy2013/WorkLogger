#ifndef DBCONNECTOR_H
#define DBCONNECTOR_H

#include <QObject>

#include <QThread>

#include <QDebug>
#include "tablemodel.h"
#include "dbtalkerfriend.h"
#include "dbtalker.h"

class DBThreadManager : public QThread
{
    Q_OBJECT
public:
    explicit DBThreadManager(TableModel* model, DBTalkerFriend* dbtalkerfriend,
    						 QObject *parent = 0);

    bool m_abort;
    TableModel* model;
    DBTalkerFriend* dbtalkerfriend;
    DBTalker* dbtalker;

protected:
    void run();
};

#endif // DBCONNECTOR_H
