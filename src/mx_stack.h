#ifndef STACK_H
#define STACK_H

#include "mx_general_public.h"

MX_Stack_Handle create_stack(Uint64 element_size, Uint64 max_elements);
void destroy_stack(MX_Stack_Handle s);
void* peek_stack(MX_Stack_Handle s);
Uint64 push_stack(MX_Stack_Handle s, void* element);
void* pop_stack(MX_Stack_Handle s);

#endif // STACK_H