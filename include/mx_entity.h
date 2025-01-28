#ifndef MX_ENTITY_H
#define MX_ENTITY_H

#include "mx_general_public.h"

MX_Entity_Handle createEntity(Uint64 initial_capacity, Uint32 flags);
void init_entity(MX_Entity_Handle entity, const char* name);
void setEntityUpdate(MX_Entity_Handle entity_handle, void (*update)(MX_Entity_Handle entity_handle, float delta_ms));
void setEntityRender(MX_Entity_Handle entity_handle, MX_RenderFunction);
void add_component(MX_Entity_Handle entity_handle, uint32_t type, void* component);
void remove_component(MX_Entity_Handle entity_handle, uint32_t type);
void destroy_entity(MX_Entity_Handle entity_handle);

#endif // MX_ENTITY_H