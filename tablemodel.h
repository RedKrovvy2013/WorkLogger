#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>
#include <Qt>
#include <QVector>
#include <QString>

class TableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    TableModel(QObject *parent = 0);
    TableModel(QVector<QVector<QString>> pData, QObject *parent = 0);

    int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const Q_DECL_OVERRIDE;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) Q_DECL_OVERRIDE;
    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex()) Q_DECL_OVERRIDE;
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex()) Q_DECL_OVERRIDE;

public slots:
	void setDataFromSignal(QVector<QVector<QString>>);

private:
	QVector<QVector<QString>> pData;
	int width;
};

#endif // TABLEMODEL_H
