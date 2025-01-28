#ifndef MX_ENTITY_INTERNAL_H
#define MX_ENTITY_INTERNAL_H

#include "mx_general_public.h"

void ensure_capacity(MX_Entity_Handle entity_handle, int needed);
void* get_component(MX_Entity_Handle entity_handle, uint32_t type);

#endif // MX_ENTITY_INTERNAL_H