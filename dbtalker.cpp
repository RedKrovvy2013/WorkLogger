#include "dbtalker.h"
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>
#include <QSqlError>
#include "pugixml.hpp"

#include <Qt>

DBTalker::DBTalker(QObject *parent) : QObject(parent)
{
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

void DBTalker::talk() {

	if(db.open()) {
		QSqlQuery query("SELECT start_time, end_time, task_duration, work_type_id, project_id, description FROM tasks");
		//2nd parameter default is QSqlDatabase, which defaults to db default...

		QVector<QVector<QString>> records;
		while(query.next()) {
			QVector<QString> record;
			for(int i=0; i != 6; ++i) {
				record.push_back(query.value(i).toString());
			}
			records.push_back(record);
		}

		emit(fireTableData(records));
	} else {
    	qDebug() << db.lastError();
	}
}

void DBTalker::request_recv(DBTalkerFriend* obj, int id, QString queryStr, QString callback) {
	QSqlQuery query(queryStr);
	QMetaObject::invokeMethod(obj, callback.toLocal8Bit().constData(), Qt::QueuedConnection,
							      Q_ARG(int, id), Q_ARG(QSqlQuery, query));
}

//static
DBTalker* DBTalker::getSingleton() {
	static DBTalker* dbtalker = new DBTalker;
	//not! giving dbtalker a QObject parent as this would make dbtalker
	//non-moveToThread-able and disallow intended moving of dbtalker
	//to the db conn thread
	return dbtalker;
	//TODO: figure out what to do when aux thread deletes DBTalker
	//      upon that thread finishing; this could happen in future apps
}
