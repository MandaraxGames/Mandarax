#ifndef MX_RENDERER_H
#define MX_RENDERER_H

#include "mx_general_public.h"

void perform_rendering(MX_Hull_Handle hull_handle);
void add_render_modification(MX_Hull_Handle hull_handle, MX_RenderFunction mod);

#endif  // MX_RENDERER_H


