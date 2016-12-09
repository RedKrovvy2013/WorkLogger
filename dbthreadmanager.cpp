#include "dbthreadmanager.h"
#include <QObject>
#include <QVector>
#include <QString>

DBThreadManager::DBThreadManager(QObject *parent)
            : QThread(parent),
			  dbtalker(DBTalker::getSingleton()) {
	dbtalker->moveToThread(this);
    //guarantees that dbtalker has db conn thread affinity,
    //in case singleton initialization call happened on main thread
	//...also, must push from main thread because QObjects are
	//not thread-safe
	//...aaand, 'this' is a QThread that has main thread affinity
	//but is used for denoting which thread to push to, which is the
	//auxiliary thread that this QThread is managing.

	connect( this, SIGNAL(finished()), dbtalker, SLOT(deleteLater()) );
	//dbtalker singleton has no parent, so if this thread exits while
	//application is still running, dbtalker will outlive thread it has
	//affinity for, which is a no-no ... so making sure to cleanup dbtalker
	//for potential case of thread prematurely exiting.
}

void DBThreadManager::run() {
    exec();
}
