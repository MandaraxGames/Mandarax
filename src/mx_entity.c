#include "mx_entity.h"
#include "mx_general_internal.h"

MX_Entity_Handle createEntity(Uint64 initial_capacity, Uint32 flags) {
  MX_Entity* entity = (MX_Entity*)SDL_malloc(sizeof(MX_Entity));
  if (!entity) return NULL;
  SDL_memset(entity, 0, sizeof(MX_Entity));
  entity->capacity = initial_capacity;
  entity->components = initial_capacity > 0 ? SDL_malloc(sizeof(void*) * entity->capacity) : NULL;
  if (!entity->components) return (MX_Entity_Handle)entity;
  SDL_memset(entity->components, 0, sizeof(entity->components));
  
  if (flags & MX_COMPONENT_POSITION) {
    MX_Point2D* pos = SDL_malloc(sizeof(MX_Point2D));
    SDL_memset(pos, 0, sizeof(MX_Point2D));
    add_component((MX_Entity_Handle)entity, MX_COMPONENT_POSITION, (void*)pos);
  }
  
  if (flags & MX_COMPONENT_SPRITE) {
    MX_Sprite* sprite = SDL_malloc(sizeof(MX_Sprite));
    SDL_memset(sprite, 0, sizeof(MX_Sprite));
    add_component((MX_Entity_Handle)entity, MX_COMPONENT_SPRITE, (void*)sprite);
  }
  
  if (flags & MX_COMPONENT_PHYSICS2D) {
    MX_PhysicsBody2D* bod = SDL_malloc(sizeof(MX_PhysicsBody2D));
    SDL_memset(bod, 0, sizeof(MX_PhysicsBody2D));
    add_component((MX_Entity_Handle)entity, MX_COMPONENT_PHYSICS2D, (void*)bod);
  }
  
  entity->mask = flags;
  
  return (MX_Entity_Handle)entity;
}

void init_entity(MX_Entity_Handle entity_handle, int argc, void* argv[]) {
  MX_Entity* entity = (MX_Entity*)entity_handle;
  MX_Point2D* pos = get_position(entity_handle);
  MX_PhysicsBody2D* pb2d = get_physics2d(entity_handle);
  SDL_strlcpy(entity->name, (char*)argv[0], 32);
  pos->x = (Uint64)argv[1];
  pos->y = (Uint64)argv[2];
  pb2d->body.x = (Uint64)argv[1];
  pb2d->body.y = (Uint64)argv[2];
  pb2d->body.width = (Uint64)argv[3];
  pb2d->body.height = (Uint64)argv[4];
}

void setEntityUpdate(MX_Entity_Handle entity_handle, void (*update)(MX_Entity_Handle, float)) {
  MX_Entity* entity = (MX_Entity*)entity_handle;
  entity->update = update;
}

void setEntityRender(MX_Entity_Handle entity_handle, MX_RenderFunction render) {
  MX_Entity* entity = (MX_Entity*)entity_handle;
  entity->components[1] = render;
}

void ensure_capacity(MX_Entity_Handle entity_handle, int needed) {
  MX_Entity* entity = (MX_Entity*)entity_handle;
  if (entity->components == NULL) {
    entity->capacity = needed*2;
    entity->components = malloc(sizeof(void*) * entity->capacity);
  }
  if (entity->capacity >= needed) return;
  while (entity->capacity < needed) entity->capacity *= 2;
  entity->components = realloc(entity->components, sizeof(void*) * entity->capacity);
}

void add_component(MX_Entity_Handle entity_handle, uint32_t type, void* component) {
  MX_Entity* entity = (MX_Entity*)entity_handle;
  ensure_capacity(entity_handle, entity->count + 1);
  
  // Store the mapping from type to index
  entity->comp_to_index[type] = entity->count;
  entity->mask |= (1 << type);
  
  // Add the component
  entity->components[entity->count++] = component;
}

void* get_component(MX_Entity_Handle entity_handle, uint32_t type) {
  MX_Entity* entity = (MX_Entity*)entity_handle;
  if (!(entity->mask & (1 << type))) return NULL;
  return entity->components[entity->comp_to_index[type]];
}

void remove_component(MX_Entity_Handle entity_handle, uint32_t type) {
  MX_Entity* entity = (MX_Entity*)entity_handle;
  if (!(entity->mask & (1 << type))) return;
  
  uint8_t index = entity->comp_to_index[type];
  
  // If not the last component, move last one to this spot
  if (index < entity->count - 1) {
    entity->components[index] = entity->components[entity->count - 1];
    
    // Update the index for the moved component
    for(int i = 0; i < MAX_ENTITY_COMPONENTS; i++) {
      if (entity->comp_to_index[i] == entity->count - 1) {
        entity->comp_to_index[i] = index;
        break;
      }
    }
  }
  
  entity->comp_to_index[type] = 0xFF;  // Mark as not present
  entity->mask &= ~(1 << type);        // Clear the bit
  entity->count--;
}

void destroy_entity(MX_Entity_Handle entity_handle) {
  MX_Entity* entity = (MX_Entity*)entity_handle;
  for(int i = 0; i < entity->count; i++) {
    free(entity->components[i]);
  }
  SDL_free(entity->components);
  SDL_free(entity);
}

// Component Functions
MX_Point2D* get_position(MX_Entity_Handle entity_handle) {
  return (MX_Point2D*)get_component(entity_handle, MX_COMPONENT_POSITION);
}

MX_Sprite* get_sprite(MX_Entity_Handle entity_handle) {
  return (MX_Sprite*)get_component(entity_handle, MX_COMPONENT_SPRITE);
}

MX_PhysicsBody2D* get_physics2d(MX_Entity_Handle entity_handle) {
  return (MX_PhysicsBody2D*)get_component(entity_handle, MX_COMPONENT_PHYSICS2D);
}