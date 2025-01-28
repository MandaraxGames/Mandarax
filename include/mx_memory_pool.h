#ifndef MX_MEMORY_POOL_H
#define MX_MEMORY_POOL_H

#include "mx_general_public.h"

void* create_pool(void);
void* pool_alloc(void* pool, size_t size);
void pool_free(void* pool, void* ptr);

#endif // MX_MEMORY_POOL_H