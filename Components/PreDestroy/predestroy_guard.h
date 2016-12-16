#ifndef PREDESTROY_GUARD_H
#define PREDESTROY_GUARD_H

#include "predestroy_signaller.h"

class PreDestroy_Guard
{
public:
    PreDestroy_Guard(PreDestroy_Signaller*);
    ~PreDestroy_Guard();
private:
    PreDestroy_Signaller *predestroy_signaller;
};

#endif // PREDESTROY_GUARD_H
