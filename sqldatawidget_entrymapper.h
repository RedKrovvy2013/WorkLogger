#ifndef SQLDATAWIDGET_ENTRYMAPPER_H_
#define SQLDATAWIDGET_ENTRYMAPPER_H_

/* This has only been tested to work with SqlRelationalTableModel,
 * thus the more specific name SqlDataWidget_EntryMapper.
 * 
 * Attempted to make code model-independent
 * (e.g. - row insertion is achieved without using insertRecord()).
 * Buut, inserted model data wasn't submitting to db without use
 * of SqlTableModel-specific method, submitAll().
 * 
 * Also, there is no orientation coding, yet; each widget is mapped
 * to a column. There is no clear or removeMapping(), yet.
 * There is no tracking of indexing, though, like in
 * QDataWidgetMapper, but this is not needed since the data
 * is getting inserted and not edited.
 * 
 * This code was built after studying QDataWidgetMapper source,
 * so the code is similar in construction.
 */

#include <QObject> 
#include <QList>
#include <QWidget>
#include <QByteArray>
#include <QSqlTableModel>
#include <memory>
#include <QVariant>

struct PreEntryItem;
struct DataWidgetEntryItem;
struct ManualEntryItem;

class SqlDataWidget_EntryMapper : public QObject {
	Q_OBJECT
public:
	explicit SqlDataWidget_EntryMapper(QSqlTableModel *model, QObject *parent = 0);
	
	void addMapping(QObject *object, int column, const QByteArray &property);
	void addMapping(const int column, const QVariant& value);
	QSqlTableModel *getModel() const;
	
signals:
	void dataInserted();

public slots:
	bool submit();

private:
	QSqlTableModel *model;
	QList<PreEntryItem> entryMap;
	bool submit_helper(int column, const QVariant& val);
private slots:
	void modelDestroyed();
};

struct PreEntryItem {
	std::shared_ptr<DataWidgetEntryItem> data_item_p_;
	std::shared_ptr<ManualEntryItem> manual_item_p_;
	bool isWidgetEntry_;
	PreEntryItem(std::shared_ptr<DataWidgetEntryItem> data_item_p,
			     std::shared_ptr<ManualEntryItem> manual_item_p,
				 bool isWidgetEntry)
					: data_item_p_(data_item_p),
					  manual_item_p_(manual_item_p),
					  isWidgetEntry_(isWidgetEntry) { }
};

struct DataWidgetEntryItem {
	QObject *object_;
	int column_;
	QByteArray property_;
	DataWidgetEntryItem(QObject *o, int c, const QByteArray &p)
		: object_(o), column_(c), property_(p) { }
};

struct ManualEntryItem {
	int column_;
	QVariant value_;
	ManualEntryItem(int column, const QVariant& value)
		: column_(column), value_(value) { }
};

#endif
