#ifndef STACK_H
#define STACK_H

#include "mx_common.h"

void* create_stack(Uint64 element_size, Uint64 max_elements);
void destroy_stack(void* s);
void* peek_stack(void* s);
Uint64 push_stack(void* s, void* element);
void* pop_stack(void* s);

#endif // STACK_H