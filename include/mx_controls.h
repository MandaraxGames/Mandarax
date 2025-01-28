#ifndef MX_CONTROLS_H
#define MX_CONTROLS_H

#include "mx_general_public.h"

void *create_controls(void);
void destroy_controls(void *ctrl_pointer);
void handle_input(void *hull_pointer);

#endif // MX_CONTROLS_H
