#ifndef DBTALKERFRIEND_H
#define DBTALKERFRIEND_H

#include <QObject>
#include <QString>
#include <QSqlQuery>
#include <unordered_map>

class DBTalker;

class DBTalkerFriend : public QObject
{
    Q_OBJECT
public:
    explicit DBTalkerFriend(QObject *parent = 0);

    virtual void request(int, QString);

signals:
	void reply_recv(int, QSqlQuery);

private:

	int generateId();
	int idIndex;

	DBTalker* dbtalker_;
};

#endif // DBTALKERFRIEND_H
