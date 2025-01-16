#include "mx_entity.h"
#include "mx_general_internal.h"

MX_Entity_Handle createEntity(MX_Manifest_Handle manifest_handle, Uint32 flags) {
    MX_Entity* entity;
    
    entity = (MX_Entity*)malloc(sizeof(MX_Entity));
    if (!entity) return NULL;
    
    /* Initialize components based on flags */
    if (flags & MX_COMPONENT_POSITION) {
        entity->components[0] = malloc(sizeof(MX_Position2D));
    }
    
    if (flags & MX_COMPONENT_SPRITE) {
        entity->components[1] = malloc(sizeof(MX_Sprite));
    }
    
    entity->active_components = flags;
    
    return (MX_Entity_Handle)entity;
}