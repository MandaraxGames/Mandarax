#include "mx_renderer.h"
#include "mx_general_internal.h"

void *create_renderer(SDL_Renderer *sdl_renderer) {
  struct MX_Renderer *renderer = (struct MX_Renderer*)SDL_malloc(sizeof(struct MX_Renderer));
  SDL_memset(renderer, 0, sizeof(MX_Renderer));
  renderer->renderer = sdl_renderer;
  renderer->mod_count = 0;

  return (MX_Renderer_Handle)renderer;
}

void destroy_renderer(MX_Renderer_Handle renderer_handle) {
  struct MX_Renderer *renderer = (struct MX_Renderer*)renderer_handle;

  if (renderer) {
    if (renderer->renderer) {
      SDL_DestroyRenderer(renderer->renderer);
    }
    SDL_free(renderer);
  }
}

void perform_rendering(void *hull_handle) {
  struct MX_Renderer *renderer = (struct MX_Renderer*)hull_handle;

  if (renderer && renderer->renderer) {
    SDL_SetRenderDrawColor(renderer->renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer->renderer);

    for (int i = 0; i < renderer->mod_count; i++) {
      renderer->render_modifications[i](hull_handle);
    }

    SDL_RenderPresent(renderer->renderer);
  }
}

void add_render_modification(void *hull_handle, MX_Render_Function mod) {
  struct MX_Renderer *renderer = (struct MX_Renderer*)hull_handle;

  if (renderer && renderer->mod_count < MAX_MODIFICATIONS) {
    renderer->render_modifications[renderer->mod_count++] = mod;
    SDL_Log("Added modification number: %d", renderer->mod_count);
  } else {
    SDL_Log("Max modifications reached, cannot add more.\n");
  }
}
