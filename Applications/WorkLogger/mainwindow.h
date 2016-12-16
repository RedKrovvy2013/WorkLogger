#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QList>
#include "mainwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow();

private:
    MainWidget *main_widget;
    QAction *action_open_workTypes;
    QAction *action_open_projects;

signals:
	void managerDialogUpdated();

private slots:
    void open_workTypes();
    void open_projects();
};

#endif // MAINWINDOW_H
