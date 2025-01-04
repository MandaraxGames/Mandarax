#include "../include/renderer.h"
#include "../include/general_internal.h"

void *create_renderer(SDL_Renderer *sdl_renderer) {
  Renderer *renderer = (Renderer *)SDL_malloc(sizeof(Renderer));
  SDL_memset(renderer, 0, sizeof(Renderer));
  renderer->renderer = sdl_renderer;
  renderer->mod_count = 0;

  return (void*)renderer;
}

void destroy_renderer(void *renderer_pointer) {
  Renderer *renderer = (Renderer *)renderer_pointer;

  if (renderer) {
    if (renderer->renderer) {
      SDL_DestroyRenderer(renderer->renderer);
    }
    SDL_free(renderer);
  }
}

void perform_rendering(void *hull_pointer) {
  Renderer *renderer = (Renderer*)((Hull*)hull_pointer)->renderer;

  if (renderer && renderer->renderer) {
    SDL_SetRenderDrawColor(renderer->renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer->renderer);

    for (int i = 0; i < renderer->mod_count; i++) {
      renderer->render_modifications[i](hull_pointer);
    }

    SDL_RenderPresent(renderer->renderer);
  }
}

void add_render_modification(void *hull_pointer, RenderFunction mod) {
  Renderer *renderer = (Renderer*)((Hull*)hull_pointer)->renderer;

  if (renderer && renderer->mod_count < MAX_MODIFICATIONS) {
    renderer->render_modifications[renderer->mod_count++] = mod;
    SDL_Log("Added modification number: %d", renderer->mod_count);
  } else {
    SDL_Log("Max modifications reached, cannot add more.\n");
  }
}
