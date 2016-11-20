#include "mainwindow.h"
#include <QAction>
#include <QMenuBar>
#include <QSqlTableModel>
#include <QDesktopWidget>
#include <functional>
#include "item_manager_dialog.h"
#include "btn_and_lineedit_widget.h"
#include "dropdown_widget.h"
#include "worklogmodel_container.h"

MainWindow::MainWindow()
{
    main_widget = new MainWidget(this);
    setCentralWidget(main_widget);
    setWindowTitle(tr("Work Logger"));

    action_open_workTypes = new QAction(tr("Work Categories Manager"), this);
    action_open_projects = new QAction(tr("Projects Manager"), this);

    QMenuBar *menu = menuBar();
    menu->addAction(action_open_workTypes);
    menu->addAction(action_open_projects);

    connect(action_open_workTypes, SIGNAL(triggered()), this, SLOT(open_workTypes()));
    connect(action_open_projects, SIGNAL(triggered()), this, SLOT(open_projects()));

    //hooking up hack to get drop-downs to not go blank after opening item manager
    //   - also tried making these direct calls in open_dialog()s, but it wasn't working!

    DropDownWidget *dd_work_types =
        main_widget->get_worklogger_widget()->get_pres_model()->get_dropdown_work_types();

    connect(this, &MainWindow::managerDialogUpdated,
        	std::bind(&QComboBox::setCurrentIndex, dd_work_types, 0 ));

    DropDownWidget *dd_projects =
        main_widget->get_worklogger_widget()->get_pres_model()->get_dropdown_projects();

    connect(this, &MainWindow::managerDialogUpdated,
			std::bind(&QComboBox::setCurrentIndex, dd_projects, 0 ));


    //cosmetics------
    resize(QDesktopWidget().availableGeometry(this).size() * 0.7);
}

void MainWindow::open_workTypes() {
	static ItemManagerDialog* d = new ItemManagerDialog("work_types");
	d->exec();
	emit managerDialogUpdated();
	WorkLogModelContainer::getSingleInstance()->getModel()->relationModel(4)->select();
}
//TODO: maybe have open(QString tableName)...
void MainWindow::open_projects() {
	static ItemManagerDialog* d = new ItemManagerDialog("projects");
	d->exec();
	emit managerDialogUpdated();
	WorkLogModelContainer::getSingleInstance()->getModel()->relationModel(5)->select();
}
