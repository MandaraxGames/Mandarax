#ifndef RENDERER_H
#define RENDERER_H

#include "mx_general_public.h"

MX_Renderer_Handle create_renderer(SDL_Renderer *sdl_renderer);
void destroy_renderer(MX_Renderer_Handle renderer_handle);
void perform_rendering(MX_Hull_Handle hull_handle);
void add_render_modification(MX_Hull_Handle hull_handle, MX_RenderFunction mod);

#endif  // RENDERER_H


