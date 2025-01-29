#include "mx_general_internal.h"

SDL_Texture* load_texture(SDL_Renderer* context, const char* path) {
  SDL_Texture* texture = NULL;
  
  // Load the image into a surface
  SDL_Surface* loaded_surface = IMG_Load(path);
  if (!loaded_surface) {
    SDL_Log("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
    return NULL;
  }
  
  // Create texture from surface
  texture = SDL_CreateTextureFromSurface(context, loaded_surface);
  if (!texture) {
    SDL_Log("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
  }
  
  // Free the temporary surface
  SDL_FreeSurface(loaded_surface);
  
  return texture;
}

void set_sprite(MX_Entity_Handle entity_handle, SDL_Renderer* context, const char* path) {
  MX_Sprite* sprite = get_sprite(entity_handle);
  if (!sprite) return;
  
  // Clean up any existing texture
  if (sprite->texture) {
    SDL_DestroyTexture(sprite->texture);
  }
  
  sprite->texture = load_texture(context, path);
  if (sprite->texture) {
    // Get the texture dimensions
    SDL_QueryTexture(sprite->texture, NULL, NULL, &sprite->width, &sprite->height);
    
    // Initialize source rect to full texture
    sprite->src_rect = (SDL_Rect){0, 0, sprite->width, sprite->height};
    
    // Initialize dest rect - you might want to use the entity's position here
    sprite->dest_rect = (SDL_Rect){0, 0, sprite->width, sprite->height};
    
    sprite->angle = 0.0;
    sprite->center = NULL;  // Center of texture
    sprite->flip = SDL_FLIP_NONE;
  }
}