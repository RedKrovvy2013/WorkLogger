#ifndef FAKEDBTALKERFRIEND_H
#define FAKEDBTALKERFRIEND_H

#include "dbtalkerfriend.h"
#include <QObject>

class FakeDBTalkerFriend : public DBTalkerFriend
{
	Q_OBJECT
public:
    FakeDBTalkerFriend(QObject* parent = 0);

    void request(int, QString); //override
};

#endif // FAKEDBTALKERFRIEND_H
