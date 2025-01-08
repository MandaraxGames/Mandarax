#include "mx_stack.h"
#include "mx_general_internal.h"

void* create_stack(Uint64 element_size, Uint64 max_elements) {
    Stack* s = (Stack*)SDL_malloc(sizeof(Stack));
    if (!s) {
        SDL_Log("Failed to allocate memory for Stack.");
        return NULL;
    }
    SDL_memset(s, 0, sizeof(Stack));
    
    s->data = SDL_malloc(element_size * max_elements);
    if (!s->data) {
        SDL_Log("Failed to allocate memory for Stack data.");
        SDL_free(s);
        return NULL;
    }
    
    s->element_size = element_size;
    s->max_elements = max_elements;
    s->top = 0;
    
    return (void*)s;
}

void destroy_stack(void* s) {
    Stack* stack = (Stack*)s;
    if (stack) {
        if (stack->data) {
            SDL_free(stack->data);
        }
        SDL_free(stack);
    }
}

void* peek_stack(void* s) {
    Stack* stack = (Stack*)s;
    
    if (stack->top == 0) {
        return NULL;
    }

    return (Uint8*)stack->data + ((stack->top - 1) * stack->element_size);
}

Uint64 push_stack(void* s, void* element) {
    Stack* stack = (Stack*)s;
    
    if (stack->top >= stack->max_elements) {
        SDL_LogError(SDL_LOG_PRIORITY_CRITICAL, "Stack overflow - cannot push element");
        return 0;
    }
    
    void* dest = (Uint8*)stack->data + (stack->top * stack->element_size);
    SDL_memcpy(dest, element, stack->element_size);
    stack->top++;
    
    return 1;
}

void* pop_stack(void* s) {
    Stack* stack = (Stack*)s;
    
    if (stack->top == 0) {
        return NULL;
    }
    
    stack->top--;
    return (Uint8*)stack->data + (stack->top * stack->element_size);
}
