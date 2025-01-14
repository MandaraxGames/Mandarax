#include "mx_renderer.h"
#include "mx_general_internal.h"

void *create_renderer(SDL_Renderer *sdl_renderer) {
  MX_Renderer *renderer = (MX_Renderer*)SDL_malloc(sizeof(MX_Renderer));
  SDL_memset(renderer, 0, sizeof(MX_Renderer));
  renderer->renderer = sdl_renderer;
  renderer->mod_count = 0;

  return (MX_Renderer_Handle)renderer;
}

void destroy_renderer(MX_Renderer_Handle renderer_handle) {
  MX_Renderer *renderer = (MX_Renderer*)renderer_handle;

  if (renderer) {
    if (renderer->renderer) {
      SDL_DestroyRenderer(renderer->renderer);
    }
    SDL_free(renderer);
  }
}

void perform_rendering(MX_Hull_Handle hull_handle) {
  MX_Renderer *renderer = (MX_Renderer*)((MX_Hull*)hull_handle)->renderer;

  if (renderer && renderer->renderer) {
    SDL_SetRenderDrawColor(renderer->renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer->renderer);

    for (int i = 0; i < renderer->mod_count; i++) {
      renderer->render_modifications[i](hull_handle);
    }

    SDL_RenderPresent(renderer->renderer);
  }
}

void add_render_modification(MX_Hull_Handle hull_handle, MX_RenderFunction mod) {
  MX_Renderer *renderer = (MX_Renderer*)((MX_Hull*)hull_handle)->renderer;

  if (renderer && renderer->mod_count < MAX_MODIFICATIONS) {
    renderer->render_modifications[renderer->mod_count++] = mod;
    SDL_Log("Added modification number: %d", renderer->mod_count);
  } else {
    SDL_Log("Max modifications reached, cannot add more.\n");
  }
}
