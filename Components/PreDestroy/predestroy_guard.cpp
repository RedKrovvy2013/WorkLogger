#include "predestroy_guard.h"

PreDestroy_Guard::PreDestroy_Guard(PreDestroy_Signaller* predestroy_signaller)
	: predestroy_signaller(predestroy_signaller) { }

PreDestroy_Guard::~PreDestroy_Guard()
{
	delete predestroy_signaller;
}
