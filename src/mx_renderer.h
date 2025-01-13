#ifndef RENDERER_H
#define RENDERER_H

#include "mx_common.h"

MX_Renderer_Handle create_renderer(SDL_Renderer *sdl_renderer);
void destroy_renderer(MX_Renderer_Handle renderer_handle);
void perform_rendering(MX_Renderer_Handle renderer_handle);
void add_render_modification(MX_Renderer_Handle renderer_handle, MX_Render_Function mod);

#endif  // RENDERER_H


