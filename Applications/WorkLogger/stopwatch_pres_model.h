#ifndef STOPWATCH_PRES_MODEL_H
#define STOPWATCH_PRES_MODEL_H

#include <QObject>
#include "stopwatch_model.h"
#include <QString>
#include <QPushButton>
#include <QLabel>
#include "abstract_pres_model.h"
#include "stopwatch_model.h"

#include <QDebug>

class StopWatch_Pres_Model : public Abstract_Pres_Model
{
	Q_OBJECT
	Q_PROPERTY(QString timeFormatted READ getTimeFormatted)
public:
    StopWatch_Pres_Model(StopWatch_Model *dom_model,
    					 QPushButton *btn_play,
						 QPushButton *btn_pause,
						 QLabel *label,
    				     QObject *parent = 0);

    QString getTimeFormatted() const;
	QPushButton *btn_play;
	QPushButton *btn_pause;
	QLabel *label;

private:
	QString m_timeFormatted;

};

#endif // STOPWATCH_PRES_MODEL_H
