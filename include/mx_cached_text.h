#ifndef MX_CACHED_TEXT_H
#define MX_CACHED_TEXT_H

#include "mx_general_public.h"

void* create_cached_text(const char* text, Uint64 max_length);
void destroy_cached_text(void* cached_text_pointer);
void update_cached_text_texture(void* cached_text_pointer, SDL_Renderer* context);
void get_cached_text_dimensions(void* cached_text_pointer, Uint64* width, Uint64* height);
void render_cached_text(void* cached_text_pointer, SDL_Renderer* context, SDL_Rect* dstrect);
Uint64 has_remaining_text(void* cached_text_pointer);
void reset_cached_text(void* cached_text_pointer, const char* new_text);
Uint64 process_typed_character(void* cached_text_pointer, char typed);

#endif // MX_CACHED_TEXT_H