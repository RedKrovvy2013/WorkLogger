#ifndef STOPWATCHWIDGET_H
#define STOPWATCHWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include "stopwatch_model.h"
#include "stopwatch_pres_model.h"

class StopWatchWidget : public QWidget
{
	Q_OBJECT
public:
    explicit StopWatchWidget(QWidget *parent = 0);
    StopWatch_Model *get_dom_model();
    StopWatch_Pres_Model *get_pres_model();
    
private:
    QLabel *label;
    QPushButton * btn_play;
    QPushButton * btn_pause;
    
    StopWatch_Model *dom_model;
    StopWatch_Pres_Model *pres_model;
};

#endif // STOPWATCHWIDGET_H
