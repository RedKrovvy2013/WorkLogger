#include "dbtalker.h"
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>
#include <QSqlError>
#include "pugixml.hpp"

#include <Qt>

DBTalker::DBTalker(QObject *parent) : QObject(parent)
{
	//TODO: verify that this is being init'd on the db thread!
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("settings.xml");
	pugi::xml_node settings = doc.child("settings");

	db = QSqlDatabase::addDatabase("QMYSQL");

    db.setHostName(settings.attribute("hostname").value());
	db.setDatabaseName(settings.attribute("dbname").value());
	db.setUserName(settings.attribute("dbuser").value());
	db.setPassword(settings.attribute("dbpwd").value());

	if(!db.open()) {
		qDebug() << db.lastError();
	}
}

//#include <functional>
//#include <QTimer>
void DBTalker::request_recv(DBTalkerFriend* obj, int id, QString queryStr, QString callback) {

// USE! the commented code to test that ConcurrentDBTableModel::select() and select_again()
//      properly cycle in holding pattern until ConcurrentDBTableModel's setTable operation
//      series completes.

//	static int count = 0;
//	if(count != 2) {
//	    ++count;
//	    QTimer::singleShot(1000, std::bind(&DBTalker::request_recv, this, obj, id, queryStr, callback));
//		return;
//	} else {
//		count = 0;
//	}

	QSqlQuery query(queryStr);
	QMetaObject::invokeMethod(obj, callback.toLocal8Bit().constData(), Qt::QueuedConnection,
								  Q_ARG(int, id), Q_ARG(QSqlQuery, query));
}

//static
DBTalker* DBTalker::getSingleton() {
	//TODO: make this and all singletons have better singleton security/enforcement;
	//      maybe have ctor be private so it can only be called from here
	static DBTalker* dbtalker = new DBTalker;
	//not! giving dbtalker a QObject parent as this would make dbtalker
	//non-moveToThread-able and disallow intended moving of dbtalker
	//to the db conn thread
	return dbtalker;
	//TODO: figure out what to do when aux thread deletes DBTalker
	//      upon that thread finishing; this could happen in future apps
}
