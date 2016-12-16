#ifndef DbContainer_H_
#define DbContainer_H_

#include <QSqlDatabase>

//foo4
class DbContainer {
public:
	static DbContainer* getSingleInstance();
    QSqlDatabase& getDb();
private:
	explicit DbContainer();
	QSqlDatabase db;
};

#endif
