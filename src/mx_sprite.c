#include "mx_entity.h"
#include "mx_entity_internal.h"
#include "mx_entity_components.h"
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

MX_Sprite* get_sprite(MX_Entity_Handle entity_handle) {
  return (MX_Sprite*)get_component(entity_handle, MX_COMPONENT_SPRITE);
}

void set_sprite(MX_Entity_Handle entity_handle, MX_Renderer_Handle, const char* path) {
  SDL_Renderer* context = ((MX_Renderer*)MX_Renderer_Handle)->context;
  MX_Sprite* sprite = get_sprite(entity_handle);
  if (!sprite) return;
  
  // Clean up any existing texture
  if (sprite->texture) {
    SDL_DestroyTexture(sprite->texture);
  }
  
  sprite->texture = load_texture(context, path);
  if (sprite->texture) {
    // Get the texture dimensions
    SDL_QueryTexture(sprite->texture, NULL, NULL, &((int)sprite->src_rect.width), &((int)sprite->src_rect.height));
    
    sprite->angle = 0.0;
    sprite->center = (MX_Point2D){
      .x = sprite->dest_rect.width/2,
      .y = sprite->dest_rect.height/2
    };
    sprite->flip = SDL_FLIP_NONE;
  }
}