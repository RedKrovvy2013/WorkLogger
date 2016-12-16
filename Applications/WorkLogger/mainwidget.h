#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "worklogviewer_widget.h"
#include "worklogger_widget.h"

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = 0);
    WorkLogger_Widget *get_worklogger_widget();

signals:

public slots:

private:
    WorkLogger_Widget *worklogger_widget;
	WorkLogViewer_Widget *worklogviewer_widget;
};

#endif // MAINWIDGET_H
