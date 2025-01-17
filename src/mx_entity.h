#ifndef MX_ENTITY_H
#define MX_ENTITY_H

#include "mx_general_public.h"

MX_Entity_Handle createEntity(Uint32 flags);
void setEntityUpdate(MX_Entity_Handle entity_handle, void (*update)(float delta_ms));
void setEntityRender(MX_Entity_Handle entity_handle, MX_RenderFunction);

#endif // MX_ENTITY_H