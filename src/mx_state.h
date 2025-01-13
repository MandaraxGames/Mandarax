#ifndef STATE_H
#define STATE_H

#include "mx_common.h"

MX_Stack_Handle createState(MX_PushDownAutomata_Handle psd, MX_Stack_Handle* states, void* context);
void destroyState(MX_State_Handle s);
MX_PushDownAutomata_Handle createPushDownAutomata(MX_State_Handle* states, void* context);
void destroyPushDownAutomata(MX_PushDownAutomata_Handle psd);

#endif // STATE_H