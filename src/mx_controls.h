#ifndef CONTROLS_H
#define CONTROLS_H

#include "mx_common.h"

void *create_controls(void);
void destroy_controls(void *ctrl_pointer);
void handle_input(void *hull_pointer);

#endif // CONTROLS_H
