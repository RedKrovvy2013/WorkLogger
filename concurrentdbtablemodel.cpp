#include "concurrentdbtablemodel.h"
#include <QTimer>
#include <QDebug>

ConcurrentDBTableModel::ConcurrentDBTableModel(QObject *parent)
    : QAbstractTableModel(parent),
	  setTable_opSeries_count_(0),
	  width_(0),
	  dbtalkerfriend_(new DBTalkerFriend(this))
{
	connect(dbtalkerfriend_, &DBTalkerFriend::reply_recv,
				this, &ConcurrentDBTableModel::processReply);
}

int ConcurrentDBTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return pData_.size();
}

int ConcurrentDBTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return width_;
}

QVariant ConcurrentDBTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= pData_.size() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole) {
    	return pData_[index.row()][index.column()];
    }
    return QVariant();
}

QVariant ConcurrentDBTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	Q_UNUSED(orientation);
	Q_UNUSED(section);

    if (role != Qt::DisplayRole)
        return QVariant();

    //TODO: fill out this section

    return QVariant();
}

bool ConcurrentDBTableModel::insertRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginInsertRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row) {
        QVector<QString> record(columnCount(QModelIndex()), QString());
        pData_.insert(position, record);
    }

    endInsertRows();
    return true;
}

bool ConcurrentDBTableModel::removeRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginRemoveRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row) {
        pData_.removeAt(position);
    }

    endRemoveRows();
    return true;
}

bool ConcurrentDBTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{

    if (index.isValid()) {
        int row = index.row();

        QVector<QString> record = pData_.value(row);

        if(index.column() > record.size()-1)
        	return false;
        else {
        	record[index.column()] = value.toString();
        	qDebug() << index.column() << ": " << value.toString();
        }

        pData_.replace(row, record);
        emit(dataChanged(index, index));

        return true;
    }

    return false;
}

void ConcurrentDBTableModel::setTable(QString futureTablename) {
	QString query("SELECT `COLUMN_NAME` FROM `INFORMATION_SCHEMA`.`COLUMNS` "
			      "WHERE `TABLE_SCHEMA`='test_logger' AND `TABLE_NAME`='" + futureTablename + "'");
	int id = generateId();
	fxs[id] = &ConcurrentDBTableModel::setTable_end;
	QVector<QPair<QString, QString>> props;
	props.push_back(QPair<QString, QString>("futureTablename", futureTablename));
	waiting_props[id] = props;

	++setTable_opSeries_count_;
	dbtalkerfriend_->request(id, query);
}

void ConcurrentDBTableModel::setTable_end(QSqlQuery query) {
	QVector<QString> tempFieldnames;
	while(query.next()) {
		tempFieldnames.push_back(query.value(0).toString());
	}
	futureFieldnames_ = tempFieldnames;
	--setTable_opSeries_count_;
}

int ConcurrentDBTableModel::generateId() {
	return idIndex_++;
}

void ConcurrentDBTableModel::processReply(int id, QSqlQuery results) {
	auto propsMapIt = waiting_props.find(id);
	if(propsMapIt != waiting_props.end()) {
		auto props = propsMapIt->second; //current impl has props as QVector<QPair<QString, QString>>
		for(auto propsIt = props.begin(); propsIt != props.end(); ++propsIt) {
			setProperty(propsIt->first.toLocal8Bit().constData(), propsIt->second);
			//                  property                               value
			//TODO: make unit test verifying that multiple properties can be successfully set!
		}
		waiting_props.erase(propsMapIt);
	};
	auto fxIt = fxs.find(id);
	if(fxIt != fxs.end()) {
		(this->*fxIt->second)(results);
		fxs.erase(fxIt);
		//TODO: make a unit test verifying that |fxs|
		//      no longer has id member
	}
}

QString ConcurrentDBTableModel::getFutureTablename() {
	return futureTablename_;
}

void ConcurrentDBTableModel::setFutureTablename(QString futureTablename) {
	futureTablename_ = futureTablename;
}

void ConcurrentDBTableModel::select() {
	if(setTable_opSeries_count_) {
		QTimer::singleShot(200, this, &ConcurrentDBTableModel::select_again);
	} else {
		qDebug() << futureTablename_;
		QString query("SELECT ");
		for(auto fieldsIt = futureFieldnames_.begin(); fieldsIt != futureFieldnames_.end(); ++fieldsIt) {
			query += *fieldsIt;
			if( fieldsIt + 1 != futureFieldnames_.end() )
				query += ", ";
		}
		query += " FROM ";
		query += futureTablename_;

		int id = generateId();
		fxs[id] = &ConcurrentDBTableModel::select_end;

		dbtalkerfriend_->request(id, query);
	}
}

void ConcurrentDBTableModel::select_again() {
	if(setTable_opSeries_count_) {
		//TODO: optimize the timeout duration
		QTimer::singleShot(200, this, &ConcurrentDBTableModel::select_again);
	} else {
		select();
	}
}

void ConcurrentDBTableModel::select_end(QSqlQuery query) {

	if(futureFieldnames_.size() > fieldnames_.size()) {
		beginInsertColumns(QModelIndex(), fieldnames_.size() /*first*/, futureFieldnames_.size()-1 /*last*/);
		width_ = futureFieldnames_.size();
		endInsertColumns();
	} else if(futureFieldnames_.size() < fieldnames_.size()) {
		beginRemoveColumns(QModelIndex(), futureFieldnames_.size() /*first*/, fieldnames_.size()-1 /*last*/);
		width_ = futureFieldnames_.size();
		endRemoveColumns();
	}
	//The above is needed for attached views to actually show new data
	//Note: |width_| must be used for (begin|end)(Remove|Insert)Columns() fxs to work as expected

	if(rowCount(QModelIndex()) > 0)
		removeRows(0, rowCount(QModelIndex()), QModelIndex());
		//will still be old data's rowCount()

	while(query.next()) {
		//TODO: fix so that last row is on bottom, first row on top
		insertRows(0, 1, QModelIndex());
		for(int i=0; i != futureFieldnames_.size(); ++i) {
			 QModelIndex ix = index(0, i, QModelIndex());
			 setData(ix, query.value(i).toString());
			 qDebug() << query.value(i).toString();
		}
	}

	fieldnames_ = futureFieldnames_;
	tablename_ = futureTablename_;
}
