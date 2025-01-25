#include "../include/mx_stack.h"
#include "mx_stack_internal.h"
#include "mx_general_internal.h"

MX_Stack_Handle create_stack(Uint64 element_size, Uint64 max_elements) {
    MX_Stack* s = (MX_Stack*)SDL_malloc(sizeof(MX_Stack));
    if (!s) {
        SDL_Log("Failed to allocate memory for MX_Stack.");
        return NULL;
    }
    SDL_memset(s, 0, sizeof(MX_Stack));
    
    s->data = SDL_malloc(element_size * max_elements);
    if (!s->data) {
        SDL_Log("Failed to allocate memory for MX_Stack data.");
        SDL_free(s);
        return NULL;
    }
    
    s->element_size = element_size;
    s->max_elements = max_elements;
    s->top = 0;
    
    return (MX_Stack_Handle)s;
}

void destroy_stack(MX_Stack_Handle s) {
    MX_Stack* stack = (MX_Stack*)s;
    if (stack) {
        if (stack->data) {
            SDL_free(stack->data);
        }
        SDL_free(stack);
    }
}

void* peek_stack(MX_Stack_Handle s) {
    MX_Stack* stack = (MX_Stack*)s;
    
    if (stack->top == 0) {
        return NULL;
    }

    return (Uint8*)stack->data + ((stack->top - 1) * stack->element_size);
}

Uint64 push_stack(MX_Stack_Handle s, void* element) {
    MX_Stack* stack = (MX_Stack*)s;
    
    if (stack->top >= stack->max_elements) {
        SDL_LogError(SDL_LOG_PRIORITY_CRITICAL, "Stack overflow - cannot push element");
        return 0;
    }
    
    void* dest = (Uint8*)stack->data + (stack->top * stack->element_size);
    SDL_memcpy(dest, element, stack->element_size);
    stack->top++;
    
    return 1;
}

void* pop_stack(MX_Stack_Handle s) {
    MX_Stack* stack = (MX_Stack*)s;
    
    if (stack->top == 0) {
        return NULL;
    }
    
    stack->top--;
    return (Uint8*)stack->data + (stack->top * stack->element_size);
}
