#include "../include/stack.h"
#include "../include/general_internal.h"

void *create_stack() {
  Stack *s = (Stack*)SDL_malloc(sizeof(Stack));
  SDL_memset(s, 0, sizeof(Stack));
  
  if (!s) {
    SDL_Log("Failed to allocate memory for Stack.");
    return NULL;
  }
  
  s->end = MAX_STACK_SIZE;
  s->top = 0;
  
  return (void*)s;
}

void destroy_stack(void *s) {
  Stack *stack = (Stack*)s;
  SDL_free(stack);
}

char peek_on_stack(void *s) {
  Stack *stack = (Stack*)s;
  
  if (stack->top == 0) {
    return '\0';
  }

  return stack->stack[stack->top - 1];
}

Uint64 push_on_stack(void *s, char symbol) {
  Stack *stack = (Stack*)s;
  
  if (stack->top >= stack->end) {
    SDL_LogError(SDL_LOG_PRIORITY_CRITICAL, "stack overflow at %s:%d; %c not added");
    return 0;
  }
  
  stack->stack[stack->top++] = symbol;
  return 1;
}

char pop_off_stack(void *s) {
  Stack *stack = (Stack*)s;
    
  if (stack->top == 0) {
    return '\0';
  }
    
  stack->top--;
  char el = stack->stack[stack->top];
  stack->stack[stack->top] = '\n';
  
  return el;
}