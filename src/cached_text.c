#include "../include/cached_text.h"
#include "../include/stack.h"
#include "../include/general_internal.h"

void *create_cached_text(const char *word) {
  CachedText *text = (CachedText*)SDL_malloc(sizeof(CachedText));
  SDL_memset(text, 0, sizeof(CachedText));
  
  text->word_stack = create_stack();
  text->word_stack->end = MAX_STACK_SIZE;
  SDL_strlcpy(text->word_stack->stack, word, MAX_STACK_SIZE);
  text->word_stack->top = SDL_strlen(word);
  
  text->texture = NULL;
  text->width = 0;
  text->height = 0;
  
  return (void*)text;
}

void destroy_cached_text(void *cached_text_pointer) {
  CachedText *text = (CachedText*)cached_text_pointer;
  
  if (text->texture) {
    SDL_DestroyTexture(text->texture);
  }
  destroy_stack(text->word_stack);
  SDL_free(text);
}

void update_cached_text_texture(void *cached_text_pointer, SDL_Renderer *renderer) {
  CachedText *text = (CachedText*)cached_text_pointer;
  
  if (text->texture) {
    SDL_DestroyTexture(text->texture);
    text->texture = NULL;
    text->width = 0;
    text->height = 0;
  }
  
  SDL_Color color = {255, 255, 255};
  SDL_Surface* surface = TTF_RenderText_Solid(font, text->word_stack->stack, color);
  if (!surface) {
    SDL_Log("Unable to create text surface: %s", TTF_GetError());
    return;
  }
  
  text->width = (Uint64)surface->w;
  text->height = (Uint64)surface->h;
  
  text->texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);
  
  if (!text->texture) {
    SDL_Log("Unable to create texture: %s", SDL_GetError());
    text->width = 0;
    text->height = 0;
    return;
  }
  
  Uint32 format;
  Sint32 access;
  Sint32 w, h;
  if (SDL_QueryTexture(text->texture, &format, &access, &w, &h) == 0) {
    if (text->width != (Uint64)w || text->height != (Uint64)h) {
      SDL_Log("Warning: Texture dimensions (%d, %d) don't match surface dimensions (%llu, %llu)", 
              w, h, text->width, text->height);
      text->width = (Uint64)w;
      text->height = (Uint64)h;
    }
  } else {
    SDL_Log("SDL_QueryTexture failed: %s", SDL_GetError());
    text->width = 0;
    text->height = 0;
  }
}

void get_cached_text_dimensions(void *cached_text_pointer, Uint64 *width, Uint64 *height) {
  CachedText *text = (CachedText*)cached_text_pointer;
  *width = text->width;
  *height = text->height;
}

void render_cached_text(void *cached_text_pointer, SDL_Renderer *renderer, SDL_Rect *dstrect) {
  CachedText *text = (CachedText*)cached_text_pointer;
  if (text->texture) {
    SDL_RenderCopy(renderer, text->texture, NULL, dstrect);
  }
}

Uint64 has_remaining_text(void *cached_text_pointer) {
  CachedText *text = (CachedText*)cached_text_pointer;
  return text->word_stack->top > 0;
}

void reset_cached_text(void *cached_text_pointer, const char *new_text) {
  CachedText *text = (CachedText*)cached_text_pointer;
  SDL_strlcpy(text->word_stack->stack, new_text, MAX_STACK_SIZE);
  text->word_stack->top = SDL_strlen(new_text);
  
  if (text->texture) {
    SDL_DestroyTexture(text->texture);
    text->texture = NULL;
    text->width = 0;
    text->height = 0;
  }
}

Uint64 process_typed_character(void *cached_text_pointer, char typed) {
  CachedText *text = (CachedText*)cached_text_pointer;
  Stack *word_stack = text->word_stack;
  
  if (typed == word_stack->stack[0]) {
    word_stack->top--;
    
    for (Uint64 i = 0; i < word_stack->top; i++) {
      word_stack->stack[i] = word_stack->stack[i + 1];
    }
    word_stack->stack[word_stack->top] = '\0';
    return 1;
  }
  return 0;
}