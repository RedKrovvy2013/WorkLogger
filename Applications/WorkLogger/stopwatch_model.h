#ifndef STOPWATCH_MODEL_H
#define STOPWATCH_MODEL_H

#include <QObject>
#include <QTimer>
#include <QDateTime>
#include <QTime>
#include <QString>

class StopWatch_Model : public QObject
{
    Q_OBJECT
	Q_PROPERTY(QDateTime startTime READ getStartTime)
	Q_PROPERTY(QDateTime endTime READ getEndTime)
	Q_PROPERTY(QTime accruedTime READ getAccruedTime)
	Q_PROPERTY(bool isPlaying READ getIsPlaying)
	Q_PROPERTY(bool hasStarted READ getHasStarted)
public:
    explicit StopWatch_Model(QObject *parent = 0);
    QDateTime getStartTime() const;
	QDateTime getEndTime() const;
	QTime getAccruedTime() const;
	bool getHasStarted() const;
	bool getIsPlaying() const;

signals:
//	void event(QString);
	void started();
	void stopped();
	void paused();
	void timeUpdated();

public slots:
	void start();
	void stop();
	void pause();

private slots:
	void updateTime();

private:
    QDateTime m_startTime;
	QDateTime m_endTime;
	QTime m_accruedTime;
	bool m_hasStarted;
	bool m_isPlaying;
	QTimer *timer;

};

#endif // STOPWATCH_MODEL_H
