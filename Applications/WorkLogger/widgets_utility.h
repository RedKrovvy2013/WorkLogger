#ifndef WIDGETS_UTILITY_H_
#define WIDGETS_UTILITY_H_

#include <map>
#include <QString>
#include <QByteArray>
#include <QVariant>
#include <vector>
#include <memory>

struct WidgetResetItem {
	QWidget *widget;
	QByteArray property;
	QVariant resetValue;
	WidgetResetItem(QWidget *w, const QByteArray &p, const QVariant &v)
		: widget(w), property(p), resetValue(v) { }
};

typedef std::map<QString, std::vector<std::shared_ptr<WidgetResetItem> > > WidgetResetGroupsMap;

struct WidgetPropertyFailTest {
	QWidget *widget;
	QByteArray property;
	QVariant failTest;
	WidgetPropertyFailTest(QWidget *w, const QByteArray &p, const QVariant &f)
		: widget(w), property(p), failTest(f) { }
};

#endif
