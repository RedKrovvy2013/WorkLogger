#include "mainwindow.h"
#include <QApplication>
#include <QSqlRelationalTableModel>
#include "worklogmodel_container.h"

#include "predestroy_guard.h"
#include "predestroy_signaller.h"

int main(int argc, char *argv[])
{    
    QApplication a(argc, argv);
    MainWindow mw;
    mw.show();

    a.exec();

    WorkLogModelContainer *wcp = WorkLogModelContainer::getSingleInstance();
    QSqlRelationalTableModel *worklogmodel = wcp->getModel();
    worklogmodel->submitAll();

    PreDestroy_Guard preDestroyGuard1(PreDestroy_Signaller::getSingleInstance());

    return 0;
}
