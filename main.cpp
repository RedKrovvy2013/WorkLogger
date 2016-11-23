#include "mainwindow.h"
#include <QApplication>
#include "worklogmodel_container.h"
#include "dbthreadmanager.h"
#include "tablemodel.h"

#include "predestroy_guard.h"
#include "predestroy_signaller.h"

int main(int argc, char *argv[])
{    
    QApplication a(argc, argv);
    MainWindow mw;

    WorkLogModelContainer *wcp = WorkLogModelContainer::getSingleInstance();
    TableModel *worklogmodel = wcp->getModel();
    DBThreadManager* dbthread = new DBThreadManager(worklogmodel);
    dbthread->start();

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
