#ifndef TABLEMODELTALKER_H
#define TABLEMODELTALKER_H

#include <QObject>
#include <QVector>
#include <QString>
#include <QSqlDatabase>
#include "dbtalkerfriend.h"

class DBTalker : public QObject
{
    Q_OBJECT
public:
    explicit DBTalker(QObject *parent = 0);

    static DBTalker* getSingleton();

private:
    QSqlDatabase db;

public slots:
	void request_recv(DBTalkerFriend*, int id, QString query, QString callback);
};

#endif // TABLEMODELTALKER_H
