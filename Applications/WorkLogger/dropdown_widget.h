#ifndef DROPDOWN_WIDGET_H
#define DROPDOWN_WIDGET_H

#include <QComboBox>
#include <QWidget>

class DropDownWidget : public QComboBox {
	Q_OBJECT
	Q_PROPERTY(int sqlIndex READ getSqlIndex);

public:
	DropDownWidget(QWidget *parent = 0);
	int getSqlIndex() const;
};

#endif
