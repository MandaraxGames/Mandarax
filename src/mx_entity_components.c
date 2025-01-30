#include "mx_entity.h"
#include "mx_entity_internal.h"
#include "mx_entity_components.h"
#include "mx_general_internal.h"

MX_Point2D* get_position(MX_Entity_Handle entity_handle) {
  return (MX_Point2D*)get_component(entity_handle, MX_COMPONENT_POSITION);
}

MX_Sprite* get_sprite(MX_Entity_Handle entity_handle) {
  return (MX_Sprite*)get_component(entity_handle, MX_COMPONENT_SPRITE);
}

MX_PhysicsBody2D* get_physics2d(MX_Entity_Handle entity_handle) {
  return (MX_PhysicsBody2D*)get_component(entity_handle, MX_COMPONENT_PHYSICS2D);
}

void set_position(MX_Entity_Handle entity_handle, Uint64 x, Uint64 y) {
  MX_Point2D *pos = get_position(entity_handle);
  pos->x = x;
  pos->y = y;
}

void set_physics2d(MX_Entity_Handle entity_handle, float x, float y, float width, float height) {
  MX_PhysicsBody2D *pb2d = get_physics2d(entity_handle);
  pb2d->body.x = x;
  pb2d->body.y = y;
  pb2d->body.width = width;
  pb2d->body.height = height;
}