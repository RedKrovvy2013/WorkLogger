#include "timeformatdelegate.h"
#include <QTime>

TimeFormatDelegate::TimeFormatDelegate (QString timeFormat, QObject *parent) 
   : QStyledItemDelegate(parent),
	 m_timeFormat(timeFormat) { }
	
QString TimeFormatDelegate::displayText(const QVariant & value, const QLocale & locale ) const {
	Q_UNUSED(locale);
	return value.toTime().toString(m_timeFormat);
}