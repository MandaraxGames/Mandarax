#ifndef MX_GENERAL_PUBLIC_H
#define MX_GENERAL_PUBLIC_H

//#include <stddef.h>
#include <SDL.h>
#include <SDL_stdinc.h>
#include <SDL_timer.h>
//#include <SDL_ttf.h>
//#include <SDL_image.h>

// Window Default Constants
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 576
// Game Loop Default Constants
#define DESIRED_FPS 60
#define FIXED_DELTA 1.0 / DESIRED_FPS  // 16.666ms
#define MAX_STEPS_PER_UPDATE 5        // Prevent spiral of death
// Memory Pool Default Constants
#define CACHE_LINE 64
#define BLOCK_SIZE 256
#define POOL_SIZE (1024 * 1024)  /* 1MB */
#define NUM_BLOCKS (POOL_SIZE / BLOCK_SIZE)

typedef struct {
    const char* title;
    Uint32 width;
    Uint32 height;
    Uint32 flags;          // Configuration flags
    //Uint8 renderer_count;  // Number of additional renderers
    //Uint8 manifest_count;  // Number of entity systems
} MX_Config;

typedef struct MX_Stack* MX_Stack_Handle;
typedef struct MX_State* MX_State_Handle;
typedef struct MX_PushdownAutomata* MX_PushdownAutomata_Handle;
typedef struct MX_Renderer* MX_Renderer_Handle;
typedef void (*MX_RenderFunction)(SDL_Renderer*);
typedef struct MX_Motor* MX_Motor_Handle;
typedef struct MX_Hull* MX_Hull_Handle;

#endif // MX_GENERAL_PUBLIC_H
