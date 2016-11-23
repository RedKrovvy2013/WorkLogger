#include "dbthreadmanager.h"
#include <QObject>
#include <QVector>
#include <QString>
#include "dbtalker.h"

DBThreadManager::DBThreadManager(TableModel* model, QObject *parent)
            : QThread(parent),
              m_abort(false),
              model(model)  {}

void DBThreadManager::run() {

    DBTalker* dbtalker = new DBTalker;

    qRegisterMetaType<QVector<QVector<QString>>>();
    connect(dbtalker, SIGNAL(fireTableData(QVector<QVector<QString>>)),
            model, SLOT(setDataFromSignal(QVector<QVector<QString>>)));

    dbtalker->talk();

    exec();
}
