#ifndef DESCRIPTIONDELEGATE_H
#define DESCRIPTIONDELEGATE_H

#include <QStyledItemDelegate>
#include <QTableView>
#include <QVector>
#include <QString>

class DescriptionDelegate : public QStyledItemDelegate
{
public:
    DescriptionDelegate(QTableView*, int);

    //override
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
    		   const QModelIndex &index) const Q_DECL_OVERRIDE;

    //override
    QSize sizeHint(
    	const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;

private:
    QTableView* view;
    int column;

    void sizeAndPaint_helper(const QStyleOptionViewItem &option, const QModelIndex &index,
    						 int& width, int& padding, int& fontHeight, QVector<QString>& lines) const;
};

#endif // DESCRIPTIONDELEGATE_H
