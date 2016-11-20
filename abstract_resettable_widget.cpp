#include "abstract_resettable_widget.h"
#include <vector>
#include <memory>

AbstractResettableWidget::AbstractResettableWidget(QWidget *parent)
	: QWidget(parent) { }

void AbstractResettableWidget::reset(const QByteArray &resetGroup) {
	std::vector<std::shared_ptr<WidgetResetItem> >::const_iterator it = resets[resetGroup].begin();
	std::vector<std::shared_ptr<WidgetResetItem> >::const_iterator end = resets[resetGroup].end();
	while(it!=end) {
		(*it)->widget->setProperty((*it)->property, (*it)->resetValue);
		++it;
	}
}

