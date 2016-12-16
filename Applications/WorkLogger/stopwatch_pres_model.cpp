#include "stopwatch_pres_model.h"
#include<functional>

StopWatch_Pres_Model::StopWatch_Pres_Model(StopWatch_Model *dom_model,
											 QPushButton *btn_play,
											 QPushButton *btn_pause,
											 QLabel *label,
											QObject *parent)
	: Abstract_Pres_Model(parent, dom_model),
	  btn_play(btn_play),
	  btn_pause(btn_pause),
	  label(label)
{

	addPropertyGoal("started", btn_play, "enabled", false);
	addPropertyGoal("started", btn_pause, "enabled", true);

	addPropertyGoal("paused", btn_play, "enabled", true);
	addPropertyGoal("paused", btn_pause, "enabled", false);

	addPropertyGoal("stopped", btn_play, "enabled", true);
	addPropertyGoal("stopped", btn_pause, "enabled", false);
	addPropertyGoal("stopped", label, "text", QString("00:00:00"));

	addPropertyGoal("timeUpdated", label, "text", "timeFormatted", PG_Dynamic);

	//(1) keep since this is the first use of a property rule coming from a dom model..
	//(2) this acts as a guard against other pres models making btn_play enabled a part of new behavior;
	//    the hard and fast rule here is that any attempt to make btn_play enabled equal true
	//    will be thwarted if the stopwatch is already playing
	addPropValRule(btn_play, "enabled", true,
					QPropRule(dom_model, "isPlaying", true)
						);

	connect(btn_play, SIGNAL(clicked()), dom_model, SLOT(start()));
	connect(btn_pause, SIGNAL(clicked()), dom_model, SLOT(pause()));

	connect(dom_model, &StopWatch_Model::started,
			std::bind( &Abstract_Pres_Model::processEvent, this, "started" ));
	connect(dom_model, &StopWatch_Model::paused,
			std::bind( &Abstract_Pres_Model::processEvent, this, "paused" ));
	connect(dom_model, &StopWatch_Model::stopped,
			std::bind( &Abstract_Pres_Model::processEvent, this, "stopped" ));
	connect(dom_model, &StopWatch_Model::timeUpdated,
				std::bind( &Abstract_Pres_Model::processEvent, this, "timeUpdated" ));
}


QString StopWatch_Pres_Model::getTimeFormatted() const {
	return dom_model->property("accruedTime").toTime().toString("hh:mm:ss");
}
