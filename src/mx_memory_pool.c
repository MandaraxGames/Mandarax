#include "../include/mx_memory_pool.h"
#include "mx_memory_pool_internal.h"
#include "mx_general_internal.h"

void* create_pool(void) {
  MX_PoolManager* pool = (MX_PoolManager*)malloc(sizeof(MX_PoolManager));
  if (!pool) return NULL;
  
  Uint64 i;
  pool->free_blocks = NUM_BLOCKS;
  for (i = 0; i < NUM_BLOCKS; i++) {
    pool->blocks[i].is_free = SDL_TRUE;
    pool->blocks[i].size = 0;
  }
  return (void*)pool;
}

void* pool_alloc(void* pool_ptr, size_t size) {
  MX_PoolManager* pool = (MX_PoolManager*)pool_ptr;
  if (!pool || size > BLOCK_SIZE) return NULL;
  
  Uint64 i;
  for (i = 0; i < NUM_BLOCKS; i++) {
    if (pool->blocks[i].is_free) {
      pool->blocks[i].is_free = SDL_FALSE;
      pool->blocks[i].size = size;
      pool->free_blocks--;
      return (void*)pool->blocks[i].data;
    }
  }
  return NULL;
}

void pool_free(void* pool_ptr, void* ptr) {
  MX_PoolManager* pool = (MX_PoolManager*)pool_ptr;
  if (!pool || !ptr) return;
  
  Uint64 i;
  for (i = 0; i < NUM_BLOCKS; i++) {
    if (pool->blocks[i].data == ptr) {
      pool->blocks[i].is_free = SDL_TRUE;
      pool->blocks[i].size = 0;
      pool->free_blocks++;
      return;
    }
  }
}