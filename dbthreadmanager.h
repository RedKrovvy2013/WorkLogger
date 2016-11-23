#ifndef DBCONNECTOR_H
#define DBCONNECTOR_H

#include <QObject>

#include <QThread>

#include <QDialog>
#include <QDebug>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QSqlDatabase>
#include <QSqlError>
#include <QPushButton>
#include "tablemodel.h"

class DBThreadManager : public QThread
{
    Q_OBJECT
public:
    explicit DBThreadManager(TableModel* model, QObject *parent = 0);

    bool m_abort;
    TableModel* model;

protected:
    void run();
};

#endif // DBCONNECTOR_H
