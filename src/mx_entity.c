#include "mx_entity.h"
#include "mx_entity_internal.h"
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
    SDL_Log("adding position as a component");
    MX_Point2D* pos = SDL_malloc(sizeof(MX_Point2D));
    SDL_memset(pos, 0, sizeof(MX_Point2D));
    add_component((MX_Entity_Handle)entity, MX_COMPONENT_POSITION, (void*)pos);
    SDL_Log("Position component created - mask: %u", entity->mask);
  }
  
  if (flags & MX_COMPONENT_SPRITE) {
    SDL_Log("adding sprite as a component");
    MX_Sprite* sprite = SDL_malloc(sizeof(MX_Sprite));
    SDL_memset(sprite, 0, sizeof(MX_Sprite));
    add_component((MX_Entity_Handle)entity, MX_COMPONENT_SPRITE, (void*)sprite);
    SDL_Log("Sprite component created - mask: %u", entity->mask);
  }
  
  if (flags & MX_COMPONENT_PHYSICS2D) {
    SDL_Log("adding physicsbody2D as a component");
    MX_PhysicsBody2D* bod = SDL_malloc(sizeof(MX_PhysicsBody2D));
    SDL_memset(bod, 0, sizeof(MX_PhysicsBody2D));
    add_component((MX_Entity_Handle)entity, MX_COMPONENT_PHYSICS2D, (void*)bod);
    SDL_Log("Physics2D component created - mask: %u", entity->mask);
  }
  
  entity->mask = flags;
  
  return (MX_Entity_Handle)entity;
}

void init_entity(MX_Entity_Handle entity_handle, const char* name) {
  MX_Entity* entity = (MX_Entity*)entity_handle;
  SDL_strlcpy(entity->name, name, sizeof(entity->name));
  SDL_Log("Entity name: %s", entity->name);
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
    entity->components = SDL_malloc(sizeof(void*) * entity->capacity);
  }
  if (entity->capacity >= needed) return;
  while (entity->capacity < needed) entity->capacity *= 2;
  entity->components = SDL_realloc(entity->components, sizeof(void*) * entity->capacity);
}

uint8_t get_component_index(uint32_t component_flag) {
  switch(component_flag) {
    case MX_COMPONENT_POSITION:  return 0;
    case MX_COMPONENT_SPRITE:    return 1;
    case MX_COMPONENT_PHYSICS2D: return 2;
    case MX_COMPONENT_PHYSICS3D: return 3;
    case MX_COMPONENT_ANIMATION: return 4;
    default: 
        SDL_Log("Invalid component flag: %u", component_flag);
        return 0xFF; // Invalid index
  }
}

void add_component(MX_Entity_Handle entity_handle, uint32_t type, void* component) {
  MX_Entity* entity = (MX_Entity*)entity_handle;
  ensure_capacity(entity_handle, entity->count + 1);
  
  SDL_Log("Adding component type: %u, Current mask: %u", type, entity->mask);
  uint8_t index = get_component_index(type);
  if (index == 0xFF) {
    SDL_Log("Failed to add component - invalid type");
    return;
  }
  
  entity->comp_to_index[index] = entity->count;
  entity->mask |= type;
  SDL_Log("New mask after adding component: %u", entity->mask);
  
  entity->components[entity->count++] = component;
}

void* get_component(MX_Entity_Handle entity_handle, uint32_t type) {
    MX_Entity* entity = (MX_Entity*)entity_handle;
    SDL_Log("Getting component type: %u", type);
    SDL_Log("Current entity mask: %u", entity->mask);
    
    if (!(entity->mask & type)) {
        SDL_Log("Component not found in mask");
        return NULL;
    }
    
    uint8_t index = get_component_index(type);
    SDL_Log("Component index: %u", index);
    
    if (index == 0xFF) {
        SDL_Log("Invalid component index");
        return NULL;
    }
    
    void* component = entity->components[entity->comp_to_index[index]];
    SDL_Log("Retrieved component at index: %u", entity->comp_to_index[index]);
    
    return component;
}

void remove_component(MX_Entity_Handle entity_handle, uint32_t type) {
  MX_Entity* entity = (MX_Entity*)entity_handle;
  if (!(entity->mask & (1 << type))) return;
  
  uint8_t index = get_component_index(type);
  if (index == 0xFF) return;
  
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
    SDL_free(entity->components[i]);
  }
  SDL_free(entity->components);
  SDL_free(entity);
}
