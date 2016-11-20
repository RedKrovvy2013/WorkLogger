#include "abstract_pres_model.h"

Abstract_Pres_Model::Abstract_Pres_Model(QObject *parent, QObject *dom_model)
  : QObject(parent),
	dom_model(dom_model)
    {}

void Abstract_Pres_Model::processEvent(const QString &event) {

//---------subview--------------property---goal------//
std::map< QWidget *, std::map<QString, std::vector<PropertyGoal> > >::const_iterator view_it =
	events_toViewPropGoals[event].begin();
while(view_it!=events_toViewPropGoals[event].end()) {

  //------property---value---//
  std::map<QString, std::vector<PropertyGoal> >::const_iterator prop_it =
      events_toViewPropGoals[event][view_it->first].begin();
  while (prop_it!=events_toViewPropGoals[event][view_it->first].end()) {

  	  std::vector<PropertyGoal>::const_iterator prop_goals_it =
  	      events_toViewPropGoals[event][view_it->first][prop_it->first].begin();
	  while (prop_goals_it!=events_toViewPropGoals[event][view_it->first][prop_it->first].end()) {

		  QVariant propGoal = prop_goals_it->getIsDynamic() ?
								  property(prop_goals_it->getDynamicPropertyName().toUtf8()) :
									  prop_goals_it->getValue();

		  bool isPassedTests = true;

		  std::vector<QPropRule>::const_iterator rule_it =
			  view_toViewPropValRules[view_it->first][prop_it->first][propGoal].begin();

		  std::vector<QPropRule>::const_iterator rule_it_end =
			  view_toViewPropValRules[view_it->first][prop_it->first][propGoal].end();

			  while(rule_it!=rule_it_end) {

			  	    if(!rule_it->getRuleQualifier().getIsBypassRule(event)) {
			  	    	isPassedTests = rule_it->getIsRuleFollowed();
			  	    	if(!isPassedTests)
			  	    		break;
			  	    }

					++rule_it;
			  }//----end rules testing
		  if(isPassedTests)
		      view_it->first->setProperty(prop_it->first.toUtf8(), propGoal);
	  ++prop_goals_it;
	  }//----end property goals iteration
  ++prop_it;
  }//----end properties iteration
++view_it;
}//----end events to observing btns iteration
}

void Abstract_Pres_Model::addPropertyGoal(const QString&event,
										   QWidget *view,
										   const QString&prop,
										   const QVariant&variant,
										   PropertyGoalType pgt) {
	events_toViewPropGoals[event][view][prop].push_back(PropertyGoal(variant, pgt));
}

void Abstract_Pres_Model::addPropValRule(QWidget *view,
										  const QString&prop,
										  const QVariant&val,
										  const QPropRule& rule) {
	view_toViewPropValRules[view][prop][val].push_back(rule);
}


bool RuleQualifier::getIsBypassRule(const QString& event) const {

	if(*this!=RuleQualifier()) {
		if(type==RuleQual) {
			if(eventName!=event) {
				return true;
				//rule qualifier name does not match event, so bypass rule
			}
		}
		if(type==RuleExcept) {
			if(eventName==event) {
				return true;
				//rule is excepted by specific, so bypass rule
			}
		}
	}
	return false;
}

const bool RuleQualifier::operator!=(const RuleQualifier &rhs) const {
	if(type!=rhs.type)
		return true;
	if(eventName!=rhs.eventName)
		return true;
	return false;
}




bool QPropRule::getIsRuleFollowed() const {
	if(testType==FailTest) {
		if(object->property(property)==test) {
			return false;
		}
	}
	if(testType==PassTest) {
		if(object->property(property)!=test) {
			return false;
		}
	}
	return true;
}

RuleQualifier QPropRule::getRuleQualifier() const {
	return ruleQualifier;
}
