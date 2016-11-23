#include "dbtalker.h"
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>
#include <QSqlError>
#include "pugixml.hpp"

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
