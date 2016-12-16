#ifndef TIMEFORMATDELEGATE_H_
#define TIMEFORMATDELEGATE_H_

#include <QString>
#include <QStyledItemDelegate>
#include <QVariant>
#include <QLocale>

class TimeFormatDelegate : public QStyledItemDelegate {
public:
	TimeFormatDelegate (QString timeFormat, QObject *parent = 0);	
	virtual QString displayText(const QVariant & value, const QLocale & locale ) const;
private:
	QString m_timeFormat;
};

#endif