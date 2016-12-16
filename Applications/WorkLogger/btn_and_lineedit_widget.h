#ifndef BTN_AND_LINEEDIT_WIDGET_H
#define BTN_AND_LINEEDIT_WIDGET_H

#include <QPushButton>
#include <QLineEdit>
#include <QString>
#include "widgets_utility.h"
#include "abstract_resettable_widget.h"

class Btn_And_LineEdit_Widget : public AbstractResettableWidget
{
    Q_OBJECT
	Q_PROPERTY(QString text READ getText)
public:
    explicit Btn_And_LineEdit_Widget(QWidget *parent = 0);
    QString getText() const;

signals:
	void btn_clicked();

private:
	QPushButton * btn;
	QLineEdit * lineEdit;
};

#endif // BTN_AND_LINEEDIT_WIDGET_H
