#ifndef DRAGDROPMODEL_FACTORY_H
#define DRAGDROPMODEL_FACTORY_H

#include <QObject>
#include <QMap>
#include <QString>
#include <memory>
#include "dragdrop_sqltablemodel.h"

class DragDropModel_Factory : public QObject
{
    Q_OBJECT
public:
    explicit DragDropModel_Factory(QObject *parent = 0);

    static DragDrop_SqlTableModel* load(QString tableName, bool isFilter);

private:
    static QMap<QString, DragDrop_SqlTableModel*> models;
    static QMap<QString, DragDrop_SqlTableModel*> fullModels;
};

#endif // DRAGDROPMODEL_FACTORY_H
