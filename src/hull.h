#ifndef HULL_H
#define HULL_H

#include "common.h"

void *assemble_app(const char *title, Uint64 width, Uint64 height);
void disassemble_app(void *hull_pointer);
void render_grid(void *hull_pointer);

#endif // HULL_H
