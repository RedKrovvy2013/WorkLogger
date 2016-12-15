#include "fakedbtalkerfriend.h"
#include <QSqlQuery>

FakeDBTalkerFriend::FakeDBTalkerFriend(QObject* qobj) : DBTalkerFriend(qobj)
{

}

void FakeDBTalkerFriend::request(int id, QString queryStr) {
	emit reply_recv(id, QSqlQuery());
}
