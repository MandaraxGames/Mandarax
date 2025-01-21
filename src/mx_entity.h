#ifndef MX_ENTITY_H
#define MX_ENTITY_H

#include "mx_general_public.h"

MX_Entity_Handle createEntity(Uint64 initial_capacity, Uint32 flags);
void init_entity(MX_Entity_Handle entity, int argc, void* argv[]);
void setEntityUpdate(MX_Entity_Handle entity_handle, void (*update)(float delta_ms));
void setEntityRender(MX_Entity_Handle entity_handle, MX_RenderFunction);
void ensure_capacity(MX_Entity_Handle entity_handle, int needed);
void add_component(MX_Entity_Handle entity_handle, uint32_t type, void* component);
void* get_component(MX_Entity_Handle entity_handle, uint32_t type);
void remove_component(MX_Entity_Handle entity_handle, uint32_t type);
void destroy_entity(MX_Entity_Handle entity_handle);

// Component Functions
MX_Point2D* get_position(MX_Entity_Handle entity);
MX_Sprite* get_sprite(MX_Entity_Handle entity);
MX_Physics2D* get_physics2d(MX_Entity_Handle entity);

#endif // MX_ENTITY_H