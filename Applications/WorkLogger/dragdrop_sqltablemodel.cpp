#include "dragdrop_sqltablemodel.h"
#include <QByteArray>
#include <QDataStream>
#include <QString>
#include <QDebug>
#include <QSqlError>
#include <QModelIndex>

DragDrop_SqlTableModel::DragDrop_SqlTableModel(QSqlDatabase db, QObject * parent)
	: QSqlTableModel(parent, db) { }


Qt::DropActions DragDrop_SqlTableModel::supportedDropActions() const {
	return Qt::CopyAction | Qt::MoveAction;
}

Qt::ItemFlags DragDrop_SqlTableModel::flags(const QModelIndex &index) const {

     Qt::ItemFlags defaultFlags = QSqlTableModel::flags(index);

	 if (index.isValid())
         return Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | Qt::ItemIsEditable | defaultFlags;
	 else
		 return Qt::ItemIsDropEnabled | defaultFlags;
}

/* Copied, then manipulated for swapping 'T' and 'F',
 * from AbstractItemModel's encodeData()
 */
void DragDrop_SqlTableModel::encodeData(const QModelIndexList &indexes,
										QDataStream &stream) const {

	QModelIndexList::ConstIterator it = indexes.begin();
	for (; it != indexes.end(); ++it) {
		stream << (*it).row() << (*it).column();

		if(it->column()==2) {
			QMap<int, QVariant> swappedItemData = itemData(*it);
			QString is_active = swappedItemData[Qt::EditRole].toString();
			is_active=="T" ? is_active = "F" : is_active = "T";
			swappedItemData[Qt::EditRole] = is_active;
			swappedItemData[Qt::DisplayRole] = is_active;
			//...Edit and Display Roles are only ones currently
			stream << swappedItemData;
		} else {
			stream << itemData(*it);
		}
	}
}

/* Hidden columns, from view's perspective, do not go into what is dragged,
 * so manually adding the hidden 'is_active' column to what is dragged
 *
 * Also just copied AbstractItemModel's mimeData() in lower half of code block
 * to be able to manipulate encodeData()
 */
QMimeData *DragDrop_SqlTableModel::mimeData(const QModelIndexList &indexes) const {

	int r, c;
	for (auto it = indexes.cbegin(); it!=indexes.cend(); ++it) {
		r = it->row();
		c = it->column();
	}
	QModelIndexList indexes2 = indexes;
	indexes2.append(createIndex(r, ++c));

	if (indexes2.count() <= 0)
		return 0;
	QStringList types = mimeTypes();
	if (types.isEmpty())
		return 0;
	QMimeData *data = new QMimeData();
	QString format = types.at(0);
	QByteArray encoded;
	QDataStream stream(&encoded, QIODevice::WriteOnly);
	encodeData(indexes2, stream);
	data->setData(format, encoded);
	return data;
}

bool DragDrop_SqlTableModel::dropMimeData(const QMimeData *data, Qt::DropAction action,
                                       int row, int column, const QModelIndex &parent)
{
	Q_UNUSED(row);
	Q_UNUSED(column);
	Q_UNUSED(parent);

    if (!data || !(action == Qt::CopyAction || action == Qt::MoveAction))
        return false;

    QStringList types = mimeTypes();
    if (types.isEmpty())
        return false;
    QString format = types.at(0);
    if (!data->hasFormat(format))
        return false;

    QByteArray encoded = data->data(format);
    QDataStream stream(&encoded, QIODevice::ReadOnly);

	QVector<int> rows, columns;
	QVector<QMap<int, QVariant> > newData;

	while (!stream.atEnd()) {
		int r, c;
		QMap<int, QVariant> v;
		stream >> r >> c >> v;
		rows.append(r);
		columns.append(c);
		newData.append(v);
	}

	for (int i = 0; i < newData.size(); ++i) {
		QModelIndex modIndex = index(rows.at(i), columns.at(i), QModelIndex());
		setData(modIndex, newData.at(i)[Qt::EditRole]);
//		setItemData(modIndex, newData.at(i));
	}
//	submitAll();
//	select();

	return true;
}
