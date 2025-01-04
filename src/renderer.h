#ifndef RENDERER_H
#define RENDERER_H

#include "common.h"

typedef void (*RenderFunction)(SDL_Renderer*);

void *create_renderer(SDL_Renderer *sdl_renderer);
void destroy_renderer(void *renderer);
void perform_rendering(void *renderer);
void add_render_modification(void *renderer, RenderFunction mod);

#endif  // RENDERER_H


