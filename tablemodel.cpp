#include "tablemodel.h"
#include <QDebug>

TableModel::TableModel(QObject *parent)
    : QAbstractTableModel(parent), width(6),
	  dbtalkerfriend_(new DBTalkerFriend(this))
{
	connect(dbtalkerfriend_, &DBTalkerFriend::reply_recv,
				this, &TableModel::processReply);
}

TableModel::TableModel(QVector<QVector<QString>> pData, QObject *parent)
    : QAbstractTableModel(parent),
	  pData(pData),
	  width(6),
	  dbtalkerfriend_(new DBTalkerFriend(this))
{ }

int TableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return pData.size();
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return width;
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= pData.size() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole) {
    	return pData[index.row()][index.column()];
    }
    return QVariant();
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	Q_UNUSED(orientation);
	Q_UNUSED(section);

    if (role != Qt::DisplayRole)
        return QVariant();

    //TODO: fill out this section

    return QVariant();
}

bool TableModel::insertRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginInsertRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row) {
        QVector<QString> record(width, QString());
        pData.insert(position, record);
    }

    endInsertRows();
    return true;
}

bool TableModel::removeRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginRemoveRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row) {
        pData.removeAt(position);
    }

    endRemoveRows();
    return true;
}

bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{

    if (index.isValid()) {
        int row = index.row();

        QVector<QString> record = pData.value(row);

        if(index.column() > record.size()-1)
        	return false;
        else {
        	record[index.column()] = value.toString();
        	qDebug() << index.column() << ": " << value.toString();
        }

        pData.replace(row, record);
        emit(dataChanged(index, index));

        return true;
    }

    return false;
}

void TableModel::setDataFromSignal(QVector<QVector<QString>> data) {

	int recordSize = data[0].size();
	for(int i=0; i < data.size(); ++i) {

		insertRows(0, 1, QModelIndex());

		for(int j=0; j < recordSize; ++j) {

		    QModelIndex ix = index(0, j, QModelIndex());
		    qDebug() << setData(ix, data[i][j]);
		}
	}
}

void TableModel::setTable(QString tablename) {
	QString query("SELECT `COLUMN_NAME` FROM `INFORMATION_SCHEMA`.`COLUMNS` WHERE `TABLE_SCHEMA`='test_logger' AND `TABLE_NAME`='tasks'");
	int id = generateId();
	fxs[id] = &TableModel::setTable_end;
	dbtalkerfriend_->request(id, query);
}

void TableModel::setTable_end(QSqlQuery query) {
	while(query.next()) {
		qDebug() << query.value(0).toString();
	}
}

int TableModel::generateId() {
	return idIndex++;
}

void TableModel::processReply(int id, QSqlQuery results) {
	auto it = fxs.find(id);
	if(it != fxs.end()) {
		(this->*it->second)(results);
		fxs.erase(it);
		//TODO: make a unit test verifying that |fxs|
		//      no longer has id member
	}
}
