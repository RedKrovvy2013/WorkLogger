#include "stopwatchwidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <Qt>

StopWatchWidget::StopWatchWidget(QWidget *parent) 
    : QWidget(parent),
	  label(0),
	  btn_play(0),
	  btn_pause(0),
	  pres_model(0)
{
	QVBoxLayout *layout_1 = new QVBoxLayout();
	label = new QLabel("00:00:00");
	layout_1->addWidget(label);
	label->setFrameShadow(QFrame::Sunken);
	label->setFrameShape(QFrame::Panel);
	label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	
	QHBoxLayout *layout_2 = new QHBoxLayout();
	layout_1->addLayout(layout_2);
	btn_play = new QPushButton("Play", this);
	btn_pause = new QPushButton("Pause", this);
	btn_pause->setEnabled(false);
	btn_play->setEnabled(false);
	/*
	 * TODO: might want to toy with idea of being able to set
	 *       btn_play's init state from outside of stopwatch
	 *       to increase modularity (current pres model setup
	 *       allows for modularity of behavior but not init state!)
	 */
	layout_2->addWidget(btn_play);
	layout_2->addWidget(btn_pause);
	
	setLayout(layout_1);
	

	dom_model = new StopWatch_Model(this);
	pres_model = new StopWatch_Pres_Model(dom_model,
									      btn_play,
										  btn_pause,
										  label,
										  this);

}

StopWatch_Model * StopWatchWidget::get_dom_model() {
	return dom_model;
}

StopWatch_Pres_Model * StopWatchWidget::get_pres_model() {
	return pres_model;
}
