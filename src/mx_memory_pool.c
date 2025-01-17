#include "mx_memory_pool.h"
#include "mx_general_internal.h"

MX_PoolManager create_pool(void) {
  MX_PoolManager* pool = (MX_PoolManager*)malloc(sizeof(MX_PoolManager));
  if (!pool) return NULL;
  
  Uint64 i;
  pool->free_blocks = NUM_BLOCKS;
  for (i = 0; i < NUM_BLOCKS; i++) {
    pool->blocks[i].is_free = TRUE;
    pool->blocks[i].size = 0;
  }
  return pool;
}

void* pool_alloc(MX_PoolManager* pool, size_t size) {
  if (!pool || size > BLOCK_SIZE) return NULL;
  
  Uint64 i;
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

void pool_free(MX_PoolManager* pool, void* ptr) {
  if (!pool || !ptr) return;
  
  Uint64 i;
  for (i = 0; i < NUM_BLOCKS; i++) {
    if (pool->blocks[i].data == ptr) {
      pool->blocks[i].is_free = TRUE;
      pool->blocks[i].size = 0;
      pool->free_blocks++;
      return;
    }
  }
}