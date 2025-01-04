#ifndef STACK_H
#define STACK_H

#include "common.h"

void *create_stack(void);
void destroy_stack(void *s);
char peek_on_stack(void *s);
Uint64 push_on_stack(void *s, char symbol);
char pop_off_stack(void *s);

#endif // STACK_H
