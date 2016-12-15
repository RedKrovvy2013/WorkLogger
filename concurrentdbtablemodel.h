#ifndef CONCURRENTDBTABLEMODEL_H
#define CONCURRENTDBTABLEMODEL_H

#include <QAbstractTableModel>
#include <Qt>
#include <QVector>
#include <QString>
#include "dbtalkerfriend.h"
#include "dbtalker.h"
#include <unordered_map>
#include <QSqlQuery>
#include <QPair>

/* setTable() and select() functions begin an asynchronous series of operations.
 * Both use a xxx_end() return function that operates on data returned from
 * their intermediary calls for db data, done on the db thread.
 *
 * The |fxs| map is a means for having setTable() requests' return messages get
 * matched up with setTable_end() function; same for select(), which gets matched
 * with select_end().
 *
 * If there are 2 consecutive setTable() calls, it is expected that a select() will
 * get data based off of the last table to be set. This behavior in part relies
 * on the FIFO nature of Qt's queued connections across threads. Beware that this
 * Qt aspect is not well documented and could change in the future.
 * http://stackoverflow.com/questions/23332700/slot-invocation-order-in-qt-queued-connections
 * TODO: (maybe) Come up with impl to enforce expected behavior given
 * 	     		 multiple setTable() calls, described above. Make it be able to
 * 	     		 work with a potential Qt cross-thread setup that is not FIFO-guaranteed.
 * 	     		 (think First In, Random Out...)
 */

class ConcurrentDBTableModel : public QAbstractTableModel
{
    Q_OBJECT
    Q_PROPERTY(QString futureTablename READ getFutureTablename WRITE setFutureTablename)

public:
    ConcurrentDBTableModel(QObject *parent = 0);
    ConcurrentDBTableModel(DBTalkerFriend*, QObject *parent = 0);

    int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const Q_DECL_OVERRIDE;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) Q_DECL_OVERRIDE;
    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex()) Q_DECL_OVERRIDE;
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex()) Q_DECL_OVERRIDE;

    void setTable(QString);

    void select();

    QString getTablename();
	
private slots:
	void processReply(int id, QSqlQuery results);

	void select_again();

private:
	//TODO: consider data structure alternatives
	//		-e.g.- removeRows is going to be dreadfully slow
	//			   since it removes rows starting from lowest row index
	QVector<QVector<QString>> pData_;
	
	DBTalkerFriend* dbtalkerfriend_;
	
	//TODO: make IdGenerator class and implement idGen obj member
	int generateId();
	int idIndex_;

    typedef void (ConcurrentDBTableModel::*tablemodelfx)(QSqlQuery);
    std::unordered_map<int, tablemodelfx> fxs;
    std::unordered_map< int, QVector<QPair<QString, QString>> > waiting_props;

    int width_;

    QString tablename_;
    QVector<QString> fieldnames_;
    void setTable_end(QSqlQuery);
    int setTable_opSeries_count_;

    QString futureTablename_;
    QVector<QString> futureFieldnames_;
    //futureTablename Q_PROPERTY getter/setter
    void setFutureTablename(QString);
    QString getFutureTablename();

    void select_end(QSqlQuery);
};

#endif // CONCURRENTDBTABLEMODEL_H
