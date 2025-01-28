#ifndef MX_RENDERER_INTERNAL_H
#define MX_RENDERER_INTERNAL_H

#include "mx_general_public.h"

MX_Renderer* create_renderer(SDL_Renderer *sdl_renderer);
void destroy_renderer(MX_Renderer *renderer);

#endif  // MX_RENDERER_INTERNAL_H


