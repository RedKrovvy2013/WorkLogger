#include "stopwatch_model.h"

StopWatch_Model::StopWatch_Model(QObject *parent)
  : QObject(parent),
    timer(new QTimer()),
    m_hasStarted(false),
	m_isPlaying(false),
	m_accruedTime(QTime(0,0,0)),
	m_startTime(QDateTime()),
	m_endTime(QDateTime())
{
	connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));
}

void StopWatch_Model::start() {
	if(!m_hasStarted) {
		m_startTime = QDateTime::currentDateTime();
		m_hasStarted = true;
	}
	timer->start(1000);
	m_isPlaying = true;
	emit(started());
}

void StopWatch_Model::pause() {
	timer->stop();
	m_isPlaying = false;
	emit(paused());
}

void StopWatch_Model::stop() {
	timer->stop();
	if(m_startTime==QDateTime())
		m_startTime = QDateTime::currentDateTime();
		//for successful grabbing of data if db submits
		//stopwatch data upon stop()
	m_endTime = QDateTime::currentDateTime();
	m_hasStarted = false;
	m_isPlaying = false;
	emit(stopped());
	m_accruedTime = QTime(0,0,0);
}

QDateTime StopWatch_Model::getStartTime() const {
	return m_startTime;
}

QDateTime StopWatch_Model::getEndTime() const {
	return m_endTime;
}

QTime StopWatch_Model::getAccruedTime() const {
	return m_accruedTime;
}

bool StopWatch_Model::getHasStarted() const {
	return m_hasStarted;
}

bool StopWatch_Model::getIsPlaying() const {
	return m_isPlaying;
}

void StopWatch_Model::updateTime() {
	m_accruedTime = m_accruedTime.addSecs(1);
	emit(timeUpdated());
}
