#ifndef MX_ENTITY_COMPONENTS_H
#define MX_ENTITY_COMPONENTS_H

#include "mx_general_public.h"

MX_Point2D* get_position(MX_Entity_Handle entity);
MX_Sprite* get_sprite(MX_Entity_Handle entity);
MX_PhysicsBody2D* get_physics2d(MX_Entity_Handle entity);
void set_position(MX_Entity_Handle entity_handle, Uint64 x, Uint64 y);
void set_sprite(MX_Entity_Handle entity_handle, SDL_Renderer* context, const char* path)
void set_physics2d(MX_Entity_Handle entity_handle, float x, float y, float width, float height);

#endif // MX_ENTITY_COMPONENTS_H