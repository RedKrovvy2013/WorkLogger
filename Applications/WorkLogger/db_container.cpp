#include "db_container.h"
#include <QDebug>
#include <QSqlError>
#include "pugixml.hpp"
#include <QDialog>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QtSql>
#include <QtPlugin>

DbContainer::DbContainer() {

	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("settings.xml");
	pugi::xml_node settings = doc.child("settings");

	db = QSqlDatabase::addDatabase("QMYSQL");

    db.setHostName(settings.attribute("hostname").value());
	db.setDatabaseName(settings.attribute("dbname").value());
	db.setUserName(settings.attribute("dbuser").value());
	db.setPassword(settings.attribute("dbpwd").value());

//  db.setHostName("redkrovvy.dnsdojo.net");
//	db.setDatabaseName("timer");
//	db.setUserName("gmarius");
//	db.setPassword("roman1");

//    db.open();

// following code can be used for release build testing
// of successful db plugin connection
    if (!db.open()) {
        qDebug() << db.lastError();
        QDialog d;
        QTextEdit text;
        QHBoxLayout layout;
        d.setLayout(&layout);
        layout.addWidget(&text);
        text.setText(db.lastError().text());
        d.exec();
    }
}

DbContainer* DbContainer::getSingleInstance() {
	static DbContainer* dcp = new DbContainer();
	return dcp;
}

QSqlDatabase& DbContainer::getDb() {
	return db;
}
