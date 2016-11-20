#ifndef DRAGDROP_SQLTABLEMODEL_H
#define DRAGDROP_SQLTABLEMODEL_H

#include <QSqlTableModel>
#include <QSqlDatabase>
#include <Qt>
#include <QModelIndex>
#include <QModelIndexList>
#include <QStringList>
#include <QMimeData>
#include <QDataStream>

class DragDrop_SqlTableModel : public QSqlTableModel
{
public:
    explicit DragDrop_SqlTableModel(QSqlDatabase db = QSqlDatabase(), QObject * parent = 0);

    Qt::DropActions supportedDropActions() const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

    void encodeData(const QModelIndexList &indexes, QDataStream &stream) const;

    QMimeData* mimeData(const QModelIndexList &indexes) const;

    bool dropMimeData(const QMimeData *data,
         Qt::DropAction action, int row, int column, const QModelIndex &parent);
};

#endif // DRAGDROP_SQLTABLEMODEL_H
