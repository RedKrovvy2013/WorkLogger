#include "mainwindow.h"
#include <QApplication>
#include "worklogmodel_container.h"
#include "dbthreadmanager.h"
#include "concurrentdbtablemodel.h"

#include "predestroy_guard.h"
#include "predestroy_signaller.h"

#include <functional>
#include <QTimer>

#include <QSqlQuery>
//TODO: find a better place for this
Q_DECLARE_METATYPE(QSqlQuery);

int main(int argc, char *argv[])
{    
    QApplication a(argc, argv);
    MainWindow mw;

    WorkLogModelContainer *wcp = WorkLogModelContainer::getSingleInstance();
    ConcurrentDBTableModel *worklogmodel = wcp->getModel();


	//TODO: find a better place for this
    qRegisterMetaType<DBTalkerFriend*>();
    qRegisterMetaType<QSqlQuery>();

    //TODO: figure out what to do when setTable()/select() are errantly called before
    //      db thread is set up...
    DBThreadManager* dbthread = new DBThreadManager;
    dbthread->start();

    worklogmodel->setTable("tasks");
    worklogmodel->select();

//    QTimer::singleShot(5000, std::bind(&ConcurrentDBTableModel::setTable, worklogmodel, "tasks"));
//    QTimer::singleShot(6000, std::bind(&ConcurrentDBTableModel::select, worklogmodel));

////  could have multiple setTable()s before doing a select(),
////  where the select() actually will make width/column size of table model data change
////    worklogmodel->setTable("foo");
////    worklogmodel->setTable("bar");
//    //TODO: make unit test that verifies that "bar" table is select()'d upon;
//    //      naive impl of just using an isSettingTable bool would lead to
//    //      subsequent select() potentially select'ing upon "foo" table
//    //      which is not expected by client coder since setTable("foo") call occurred first

    mw.show();

    a.exec();

      //TODO: recover this fxality
//    WorkLogModelContainer *wcp = WorkLogModelContainer::getSingleInstance();
//    QSqlRelationalTableModel *worklogmodel = wcp->getModel();
//    worklogmodel->submitAll();
//
//    PreDestroy_Guard preDestroyGuard1(PreDestroy_Signaller::getSingleInstance());

    return 0;
}
