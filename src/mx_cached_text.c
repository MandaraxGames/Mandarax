#include "mx_cached_text.h"
#include "mx_cached_text_internal.h"
#include "mx_stack.h"
#include "mx_stack_internal.h"
#include "mx_general_internal.h"

void* create_cached_text(const char* text, Uint64 max_length) {
    MX_CachedText* cached = (MX_CachedText*)SDL_malloc(sizeof(MX_CachedText));
    if (!cached) {
        SDL_Log("Failed to allocate MX_CachedText");
        return NULL;
    }
    SDL_memset(cached, 0, sizeof(MX_CachedText));
    
    // Create stack for text (one byte per character)
    cached->text_stack = create_stack(sizeof(char), max_length);
    if (!cached->text_stack) {
        SDL_free(cached);
        return NULL;
    }
    
    // Push text into stack character by character
    for (const char* c = text; *c != '\0' && c < text + max_length; c++) {
        push_stack((MX_Stack_Handle)cached->text_stack, (void*)c);
    }
    
    return (void*)cached;
}

void destroy_cached_text(void* cached_text_pointer) {
    MX_CachedText* text = (MX_CachedText*)cached_text_pointer;
    if (text) {
        if (text->texture) {
            SDL_DestroyTexture(text->texture);
        }
        if (text->text_stack) {
            destroy_stack((MX_Stack_Handle)text->text_stack);
        }
        SDL_free(text);
    }
}

void update_cached_text_texture(void* cached_text_pointer, SDL_Renderer* renderer) {
    MX_CachedText* text = (MX_CachedText*)cached_text_pointer;
    MX_Stack* text_stack = (MX_Stack*)(text->text_stack);
    
    if (!text || !text_stack) return;

    if (text->texture) {
        SDL_DestroyTexture(text->texture);
        text->texture = NULL;
        text->width = 0;
        text->height = 0;
    }
    
    // Reconstruct current text string from stack
    char* current_text = SDL_malloc(text_stack->max_elements + 1);
    if (!current_text) return;
    
    for (Uint64 i = 0; i < text_stack->top; i++) {
        current_text[i] = *(char*)((Uint8*)text_stack->data + i);
    }
    current_text[text_stack->top] = '\0';
    
    SDL_Color color = {255, 255, 255};
    //SDL_Surface* surface = TTF_RenderText_Solid(font, current_text, color);
    SDL_free(current_text);
    
    //if (!surface) {
    //    SDL_Log("Unable to create text surface: %s", TTF_GetError());
    //    return;
    //}
    
    //text->width = surface->w;
    //text->height = surface->h;
    //text->texture = SDL_CreateTextureFromSurface(renderer, surface);
    //SDL_FreeSurface(surface);
    
    if (!text->texture) {
        SDL_Log("Unable to create texture: %s", SDL_GetError());
        text->width = 0;
        text->height = 0;
        return;
    }
}

void get_cached_text_dimensions(void* cached_text_pointer, Uint64* width, Uint64* height) {
    MX_CachedText* text = (MX_CachedText*)cached_text_pointer;
    if (text) {
        *width = text->width;
        *height = text->height;
    } else {
        *width = 0;
        *height = 0;
    }
}

void render_cached_text(void* cached_text_pointer, SDL_Renderer* renderer, SDL_Rect* dstrect) {
    MX_CachedText* text = (MX_CachedText*)cached_text_pointer;
    if (text && text->texture) {
        SDL_RenderCopy(renderer, text->texture, NULL, dstrect);
    }
}

Uint64 has_remaining_text(void* cached_text_pointer) {
    MX_CachedText* text = (MX_CachedText*)cached_text_pointer;
    MX_Stack* text_stack = (MX_Stack*)(text->text_stack);
    return text && text_stack && text_stack->top > 0;
}

void reset_cached_text(void* cached_text_pointer, const char* new_text) {
    MX_CachedText* text = (MX_CachedText*)cached_text_pointer;
    MX_Stack* text_stack = (MX_Stack*)(text->text_stack);
    if (!text || !text_stack) return;
    
    // Reset stack
    text_stack->top = 0;
    
    // Push new text into stack
    for (const char* c = new_text; 
         *c != '\0' && text_stack->top < text_stack->max_elements; 
         c++) {
        push_stack((MX_Stack_Handle)text_stack, (void*)c);
    }
    
    // Clear existing texture
    if (text->texture) {
        SDL_DestroyTexture(text->texture);
        text->texture = NULL;
        text->width = 0;
        text->height = 0;
    }
}

Uint64 process_typed_character(void* cached_text_pointer, char typed) {
    MX_CachedText* text = (MX_CachedText*)cached_text_pointer;
    MX_Stack* text_stack = (MX_Stack*)(text->text_stack);
    if (!text || !text_stack || text_stack->top == 0) return 0;
    
    // Check if typed character matches first character in stack
    char* first_char = (char*)text_stack->data;
    if (typed == *first_char) {
        // Shift all characters left by one
        for (Uint64 i = 0; i < text_stack->top - 1; i++) {
            char* curr = (char*)((Uint8*)text_stack->data + i);
            char* next = (char*)((Uint8*)text_stack->data + i + 1);
            *curr = *next;
        }
        text_stack->top--;
        return 1;
    }
    return 0;
}