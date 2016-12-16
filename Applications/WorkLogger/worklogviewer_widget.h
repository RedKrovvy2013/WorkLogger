#ifndef WORKLOGVIEWER_WIDGET_H_
#define WORKLOGVIEWER_WIDGET_H_

/*
 * keeping this class's name specific because it has sections that are
 * hard-coded specifically to a worklogviewer widget,
 * namely setting the QSqlTableModel's table to 'tasks'
 * and the prettying up of the work log view's header titles
 * 
 * If made to be more extensible, the widget's name could be ...
 * .... SqlTableWidget
 */

#include <QWidget>
#include <QSqlRelationalTableModel>
#include <QTableView>
#include <QGroupBox>
#include <QLineEdit>
#include <QPushButton>

class WorkLogViewer_Widget : public QWidget {
	Q_OBJECT
public:
	WorkLogViewer_Widget(QWidget * parent = 0);
private:
	QGroupBox *box_worklogviewer;
	QTableView *view;
	QLineEdit *line_edit_range_start;
	QLineEdit *line_edit_range_end;
	QPushButton *btn_update_range;
	QSqlRelationalTableModel *worklogmodel;

private slots:
	void updateRangeHandler();
};

#endif
