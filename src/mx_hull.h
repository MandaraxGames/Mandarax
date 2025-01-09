#ifndef HULL_H
#define HULL_H

#include "mx_common.h"

typedef struct MX_Hull* MX_Hull_Handle;

MX_Hull_Handle assemble_app(const char* title, Uint64 width, Uint64 height);
void disassemble_app(MX_Hull_Handle hull_handle);
void render_grid(MX_Hull_Handle hull_handle);

#endif // HULL_H