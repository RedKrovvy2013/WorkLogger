#ifndef ABSTRACT_RESETTABLE_WIDGET_H
#define ABSTRACT_RESETTABLE_WIDGET_H

#include <QByteArray>
#include "widgets_utility.h"
#include <QWidget>

class AbstractResettableWidget : public QWidget
{
    Q_OBJECT

public:
	explicit AbstractResettableWidget(QWidget *parent = 0);

public slots:
	virtual void reset(const QByteArray &resetGroup = "default");

protected:
	WidgetResetGroupsMap resets;
};

#endif // ABSTRACT_RESETTABLE_WIDGET_H
