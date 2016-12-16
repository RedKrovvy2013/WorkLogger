#include "predestroy_signaller.h"

PreDestroy_Signaller::PreDestroy_Signaller(QObject *parent) : QObject(parent) {}

PreDestroy_Signaller* PreDestroy_Signaller::getSingleInstance() {
	static PreDestroy_Signaller* pdsp = new PreDestroy_Signaller();
	return pdsp;
}

PreDestroy_Signaller::~PreDestroy_Signaller() {
    emit(preDestroyed());
}
