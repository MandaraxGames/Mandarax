#ifndef MX_MEMORY_POOL_H
#define MX_MEMORY_POOL_H

#include "mx_general_public.h"

struct pool_manager* create_pool(void);
void* pool_alloc(struct pool_manager* pool, size_t size);
void pool_free(struct pool_manager* pool, void* ptr);

#endif // MX_MEMORY_POOL_H