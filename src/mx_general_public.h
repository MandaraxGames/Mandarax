#ifndef GENERAL_PUBLIC_H
#define GENERAL_PUBLIC_H

#include <SDL.h>
#include <SDL_stdinc.h>
#include <SDL_timer.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 576

#define DESIRED_FPS 60
#define FIXED_DELTA 1.0 / DESIRED_FPS  // 16.666ms
#define MAX_STEPS_PER_UPDATE 5        // Prevent spiral of death

typedef struct {
    const char* title;
    Uint32 width;
    Uint32 height;
    Uint32 flags;          // Configuration flags
    //Uint8 renderer_count;  // Number of additional renderers
    //Uint8 manifest_count;  // Number of entity systems
} MxConfig;

typedef struct MX_Stack* MX_Stack_Handle;
typedef struct MX_State* MX_State_Handle;
typedef struct MX_PushDownAutomata* MX_PushDownAutomata_Handle;
typedef struct MX_Renderer* MX_Renderer_Handle;
typedef void (*MX_Render_Function)(SDL_Renderer*);
typedef struct MX_Motor* MX_Motor_Handle;
typedef struct MX_Hull* MX_Hull_Handle;

#endif // GENERAL_PUBLIC_H
