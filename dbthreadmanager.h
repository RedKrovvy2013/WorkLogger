#ifndef DBCONNECTOR_H
#define DBCONNECTOR_H

#include <QObject>

#include <QThread>

#include <QDebug>
#include "dbtalker.h"

class DBThreadManager : public QThread
{
    Q_OBJECT
public:
    explicit DBThreadManager(QObject *parent = 0);

    DBTalker* dbtalker;

protected:
    void run();
};

#endif // DBCONNECTOR_H
