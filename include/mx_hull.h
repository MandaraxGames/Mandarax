#ifndef MX_HULL_H
#define MX_HULL_H

#include "mx_general_public.h"

MX_Hull_Handle assemble_app(const char* title, Uint64 width, Uint64 height, MX_Hull_Flags flags);
void disassemble_app(MX_Hull_Handle hull_handle);
MX_Renderer_Handle getRendererHandle(MX_Hull_Handle hull_handle);
void render_grid(SDL_Renderer* context);

#endif // MX_HULL_H