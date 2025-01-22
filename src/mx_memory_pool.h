#ifndef MX_MEMORY_POOL_H
#define MX_MEMORY_POOL_H

#include "mx_general_public.h"

MX_PoolManager* create_pool(void);
void* pool_alloc(MX_PoolManager* pool, size_t size);
void pool_free(MX_PoolManager* pool, void* ptr);

#endif // MX_MEMORY_POOL_H