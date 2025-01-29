#ifndef MX_RENDERER_INTERNAL_H
#define MX_RENDERER_INTERNAL_H

#include "mx_general_public.h"

MX_Renderer_Handle create_renderer(SDL_Renderer *context);
void destroy_renderer(MX_Renderer_Handle renderer_handle);

#endif  // MX_RENDERER_INTERNAL_H


