#include "dbtalkerfriend.h"

#include <QDebug>
#include <Qt>

#include "dbtalker.h"

DBTalkerFriend::DBTalkerFriend(QObject *parent) : QObject(parent)
{
	dbtalker_ = DBTalker::getSingleton();
}

void DBTalkerFriend::request(int id, QString query) {
	QMetaObject::invokeMethod(dbtalker_, "request_recv", Qt::QueuedConnection,
                              Q_ARG(DBTalkerFriend*, this),
							  Q_ARG(int, id),
							  Q_ARG(QString, query),
							  Q_ARG(QString, "reply_recv"));
}
