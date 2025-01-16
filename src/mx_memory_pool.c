#include "mx_memory_pool.h"
#include "mx_general_internal.h"

struct pool_manager* create_pool(void)
{
    struct pool_manager* pool;
    Uint64 i;
    
    pool = (struct pool_manager*)malloc(sizeof(struct pool_manager));
    if (!pool) return NULL;
    
    pool->free_blocks = NUM_BLOCKS;
    for (i = 0; i < NUM_BLOCKS; i++) {
        pool->blocks[i].is_free = TRUE;
        pool->blocks[i].size = 0;
    }
    return pool;
}

/* Allocate memory from pool */
void* pool_alloc(struct pool_manager* pool, size_t size)
{
    Uint64 i;
    
    if (!pool || size > BLOCK_SIZE) return NULL;
    
    for (i = 0; i < NUM_BLOCKS; i++) {
        if (pool->blocks[i].is_free) {
            pool->blocks[i].is_free = FALSE;
            pool->blocks[i].size = size;
            pool->free_blocks--;
            return pool->blocks[i].data;
        }
    }
    return NULL;
}

void pool_free(struct pool_manager* pool, void* ptr)
{
    Uint64 i;
    
    if (!pool || !ptr) return;
    
    for (i = 0; i < NUM_BLOCKS; i++) {
        if (pool->blocks[i].data == ptr) {
            pool->blocks[i].is_free = TRUE;
            pool->blocks[i].size = 0;
            pool->free_blocks++;
            return;
        }
    }
}