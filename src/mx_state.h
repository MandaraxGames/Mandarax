#ifndef STATE_H
#define STATE_H

#include "mx_common.h"

typedef struct MX_State* MX_State_Handle;
typedef struct MX_PushDownAutomata* MX_PushDownAutomata_Handle;

void* createState(MX_PushDownAutomata_Handle psd, MX_Stack_Handle* states, void* context);
void destroyState(MX_State_Handle s);
void* createPushDownAutomata(MX_State_Handle* states, void* context);
void destroyPushDownAutomata(MX_PushDownAutomata_Handle psd);

#endif // STATE_H