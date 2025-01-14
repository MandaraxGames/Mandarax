#ifndef HULL_H
#define HULL_H

#include "mx_general_public.h"

MX_Hull_Handle assemble_app(const char* title, Uint64 width, Uint64 height, MX_RenderFunction game_render);
void disassemble_app(MX_Hull_Handle hull_handle);
void render_grid(MX_Hull_Handle hull_handle);

#endif // HULL_H