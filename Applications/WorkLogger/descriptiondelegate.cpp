#include "descriptiondelegate.h"

#include <QStyleOptionViewItem>
#include <QStyle>
#include <QString>
#include <QRect>
#include <QPalette>
#include <QPainter>
#include <QFontMetrics>
#include <QStringList>
#include <iterator>

#include <QDebug>

DescriptionDelegate::DescriptionDelegate(QTableView* view, int col)
	: view(view), column(col) {}

void DescriptionDelegate::paint(QPainter *painter,
							    const QStyleOptionViewItem &option,
								const QModelIndex &index) const {

	int width, padding, fontHeight;
	QVector<QString> lines;
	sizeAndPaint_helper(option, index, width, padding, fontHeight, lines);

	//TODO: regain below fxality, maybe
//	QStyleOptionViewItem opt = option;
//	initStyleOption(&opt, index);

    // draw correct background
//    opt.text = "";
//    QStyle *style = opt.widget ? opt.widget->style() : QApplication::style();
//    style->drawControl(QStyle::CE_ItemViewItem, &opt, painter, opt.widget);
//
//    QRect rect = opt.rect;
//    QPalette::ColorGroup cg = opt.state & QStyle::State_Enabled ? QPalette::Normal : QPalette::Disabled;
//    if (cg == QPalette::Normal && !(opt.state & QStyle::State_Active))
//        cg = QPalette::Inactive;
//
//    // set pen color
//    if (opt.state & QStyle::State_Selected)
//        painter->setPen(opt.palette.color(cg, QPalette::HighlightedText));
//    else
//        painter->setPen(opt.palette.color(cg, QPalette::Text));

//    opt.rect.setWidth(400);

    for(int i=0; i!=lines.size(); ++i) {
    	painter->drawText(QRect(option.rect.left()+padding, option.rect.top() + i*fontHeight + padding,
    							width, fontHeight),
    							option.displayAlignment, lines[i]);
    }

}

QSize DescriptionDelegate::sizeHint(
    	const QStyleOptionViewItem &option, const QModelIndex &index) const {

	int width, padding, fontHeight;
	QVector<QString> lines;
	sizeAndPaint_helper(option, index, width, padding, fontHeight, lines);

	//TODO: fix so that this works for situations other than column being rightmost col

	return QSize(width, fontHeight*lines.size() + padding*2);
	//width being set by QTableView
}

void DescriptionDelegate::sizeAndPaint_helper(const QStyleOptionViewItem &option, const QModelIndex &index,
    						 int& width, int& padding, int& fontHeight, QVector<QString>& lines) const {

	width = view->viewport()->rect().right() - view->columnViewportPosition(column);

    QString text = index.model()->data(index).toString();
    QStringList tokens = text.split(" ");
    QFontMetrics fontMetrics = option.fontMetrics;

    fontHeight = fontMetrics.height();
    padding = fontHeight/2;

    QString line;
    for(QStringList::const_iterator it = tokens.begin();
    	it != tokens.end(); ++it) {

    	QString token;
    	token.append(*it);
    	token.append(" ");

    	if(fontMetrics.width(line) + fontMetrics.width(token) <= width - padding*2) {
    		line.push_back(token);
    	} else {
    		lines.push_back(line);
    		line = QString();
    		line.push_back(token);
    	}

    	if( it+1 == tokens.end() ) {
    		lines.push_back(line);
    	}
    }
}
