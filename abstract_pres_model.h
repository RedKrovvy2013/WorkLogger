#ifndef ABSTRACT_PRES_MODEL_H
#define ABSTRACT_PRES_MODEL_H

#include <QObject>
#include <QVariant>
#include <QString>
#include <QByteArray>
#include <map>
#include <vector>
#include <QWidget>

class PropertyGoal;
enum PropertyGoalType  { PG_Static, PG_Dynamic };

class QPropRule;
enum RuleQualifierType { RuleQualEmpty, RuleQual, RuleExcept };
enum RuleTestType      { FailTest, PassTest };

class Abstract_Pres_Model : public QObject
{
    Q_OBJECT
private:
	//---------event---------------view------------property-----------------goal------//
	std::map< QString, std::map< QWidget*, std::map<QString, std::vector<PropertyGoal> > > > events_toViewPropGoals;

	typedef std::map<QWidget *, //<----view
				std::map<QString, //<----property
					//-------value--------------------------------------------rules---------------//
					std::map<QVariant, std::vector<QPropRule> >
				>
			> View_ToViewPropValRules_Type;

	View_ToViewPropValRules_Type view_toViewPropValRules;

public:
    void addPropertyGoal(const QString&, QWidget *, const QString&, const QVariant&,
    					 PropertyGoalType = PG_Static);
    void addPropValRule(QWidget *, const QString&, const QVariant&,
    					const QPropRule&);

public slots:
	void processEvent(const QString &event);

protected:
    QObject *dom_model;
    Abstract_Pres_Model(QObject *parent = 0, QObject *dom_model = 0);

};


class PropertyGoal {
	public:
		PropertyGoal() {};
		PropertyGoal(const QVariant& v, PropertyGoalType pgt = PG_Static)
			: value(v), propertyGoalType(pgt) { }
		QVariant getValue() const {
			return value;
		}
		QString getDynamicPropertyName() const {
			return value.toString();
		}
		bool getIsDynamic() const {
			if(propertyGoalType==PG_Dynamic)
				return true;
			else
				return false;
		}
	private:
		PropertyGoalType propertyGoalType;
		QVariant value;
};


class RuleQualifier {
private:
	RuleQualifierType type;
	QString eventName;

public:
	RuleQualifier(RuleQualifierType rqt, QString n)
		: type(rqt), eventName(n) { }
	RuleQualifier()
		: type(RuleQualEmpty), eventName(QString()) { };

	bool getIsBypassRule(const QString& event) const;
	const bool operator!=(const RuleQualifier &rhs) const;
};


class QPropRule {
	QObject *object;
	QByteArray property;
	QVariant test;
	RuleTestType testType;
	RuleQualifier ruleQualifier;

public:
	QPropRule(QObject *o, QByteArray p, QVariant t,
			  RuleTestType ttype = FailTest, RuleQualifier rq = RuleQualifier())
	  : object(o), property(p), test(t), testType(ttype), ruleQualifier(rq) {}

	bool getIsRuleFollowed() const;
	RuleQualifier getRuleQualifier() const;
};

#endif // ABSTRACT_PRES_MODEL_H
