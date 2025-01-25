#ifndef STATE_H
#define STATE_H

#include "mx_general_public.h"

MX_Stack_Handle createState(MX_PushdownAutomata_Handle psd, MX_Stack_Handle* states, void* context);
void destroyState(MX_State_Handle s);
MX_PushdownAutomata_Handle createPushdownAutomata(MX_State_Handle* states, void* context);
void destroyPushdownAutomata(MX_PushdownAutomata_Handle psd);

#endif // STATE_H