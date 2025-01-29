#include "mx_renderer.h"
#include "mx_renderer_internal.h"
#include "mx_general_internal.h"

MX_Renderer_Handle create_renderer(SDL_Renderer *context) {
  MX_Renderer *renderer = (MX_Renderer*)SDL_malloc(sizeof(MX_Renderer));
  SDL_memset(renderer, 0, sizeof(MX_Renderer));
  renderer->context = context;
  renderer->max_modifications = 10;

  renderer->render_modifications = (MX_RenderFunction*)SDL_malloc(sizeof(MX_RenderFunction)*10);
  if (!renderer->render_modifications) {
      SDL_Log("Failed to allocate render modifications");
      SDL_free(renderer);  // Clean up main structure if sub-allocation fails
      return NULL;
  }
  SDL_memset(renderer->render_modifications, 0, 
      sizeof(MX_RenderFunction) * renderer->max_modifications);
  
  return (MX_Renderer_Handle)renderer;
}

void destroy_renderer(MX_Renderer_Handle renderer_handle) {
  MX_Renderer *renderer = (MX_Renderer*)renderer_handle;

  if (renderer) {
    if (renderer->context) {
      SDL_DestroyRenderer(renderer->context);
    }
    SDL_free(renderer);
  }
}

void perform_rendering(MX_Hull_Handle hull_handle) {
  MX_Renderer *renderer = (MX_Renderer*)((MX_Hull*)hull_handle)->renderer;

  if (renderer && renderer->context) {
    SDL_SetRenderDrawColor(renderer->context, 0, 0, 0, 255);
    SDL_RenderClear(renderer->context);

    for (int i = 0; i < renderer->mod_count; i++) {
      renderer->render_modifications[i](renderer->context);
    }

    SDL_RenderPresent(renderer->context);
  }
}

void add_render_modification(MX_Hull_Handle hull_handle, MX_RenderFunction mod) {
  MX_Renderer *renderer = (MX_Renderer*)((MX_Hull*)hull_handle)->renderer;

  if (renderer && renderer->mod_count < renderer->max_modifications) {
    renderer->render_modifications[renderer->mod_count++] = mod;
    SDL_Log("Added modification number: %d", renderer->mod_count);
  } else {
    SDL_Log("Max modifications reached, cannot add more.\n");
  }
}
