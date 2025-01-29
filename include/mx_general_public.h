#ifndef MX_GENERAL_PUBLIC_H
#define MX_GENERAL_PUBLIC_H

#include <SDL.h>
#include <SDL_image.h>
//#include <SDL_ttf.h>

// Window Default Constants
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 576
// Game Loop Default Constants
#define DESIRED_FPS 60
#define FIXED_DELTA 1.0 / DESIRED_FPS  // 16.666ms
#define MAX_STEPS_PER_UPDATE 5
// Memory Pool Default Constants
#define CACHE_LINE 64
#define BLOCK_SIZE 256
#define POOL_SIZE (1024 * 1024)  /* 1MB */
#define NUM_BLOCKS (POOL_SIZE / BLOCK_SIZE)
// Default  Component Constants
#define MAX_ENTITY_COMPONENTS 32

typedef struct MX_Entity* MX_Entity_Handle;
typedef struct MX_Point2D* MX_Point2D_Handle;
typedef struct MX_FPoint2D* MX_FPoint2D_Handle;
typedef struct MX_Rect* MX_Rect_Handle;
typedef struct MX_FRect* MX_FRect_Handle;
typedef struct MX_Sprite* MX_Sprite_Handle;
typedef struct MX_PhysicsBody2D* MX_PhysicsBody2D_Handle;
typedef struct MX_Stack* MX_Stack_Handle;
typedef struct MX_State* MX_State_Handle;
typedef struct MX_PushdownAutomata* MX_PushdownAutomata_Handle;
typedef struct MX_CachedText* MX_CachedText_Handle;
typedef struct MX_Controls* MX_Controls_Handle;
typedef struct MX_Renderer* MX_Renderer_Handle;
typedef void (*MX_RenderFunction)(SDL_Renderer*);
typedef void (*MX_UpdateFunction)(float);
typedef struct MX_Manifest* MX_Manifest_Handle;
typedef struct MX_Motor* MX_Motor_Handle;
typedef struct MX_Scene* MX_Scene_Handle;
typedef struct MX_SceneManager* MX_SceneManager_Handle;
typedef struct MX_Hull* MX_Hull_Handle;

// Flag Enums
typedef enum MX_Hull_Flags {
  MX_HULL_REQUIRED       = 0x0000,  // Window + Motor + Basic Renderer (minimum)
  MX_HULL_IMAGE_RENDERER = 0x0001,  // Allows rendering PNG and soon JPEG
  MX_HULL_FONT_RENDERER  = 0x0002,  // Allows rendering fonts
  MX_HULL_FULL_RENDERER  = 0x0004,  // Allows all rendering
  MX_HULL_MANIFEST       = 0x0008,  // Entity systems
  MX_HULL_CONTROLS       = 0x0010,  // Input handling
  MX_HULL_NAVIGATION     = 0x0020,  // Scene management
  MX_HULL_UI             = 0x0040   // User interface
} MX_Hull_Flags;

typedef enum MX_EntityComponent_Flags {
  MX_COMPONENT_NONE      = 0x0000,
  MX_COMPONENT_POSITION  = 0x0001,
  MX_COMPONENT_SPRITE    = 0x0002,
  MX_COMPONENT_PHYSICS2D = 0x0004,
  MX_COMPONENT_PHYSICS3D = 0x0008,
  MX_COMPONENT_ANIMATION = 0x0010
} MX_EntityComponent_Flags;

typedef struct {
    const char* title;
    Uint32 width;
    Uint32 height;
    Uint32 flags;
} MX_Config;

typedef struct {
  Uint64 x, y;
} MX_Point2D;

typedef struct {
  float x, y;
} MX_FPoint2D;

typedef struct {
  Uint64 x, y, width, height;
} MX_Rect;

typedef struct {
  float x, y, width, height;
} MX_FRect;

typedef struct {
  MX_Rect src_rect;
  MX_Rect dest_rect;
  MX_Point2D center;
  Uint64 scale_x, scale_y;
  double angle;
  SDL_RendererFlip flip;  // Flip flags
  SDL_Texture* texture;
  void (*render)(MX_Sprite_Handle, struct SDL_Renderer*);
} MX_Sprite;

typedef struct {
  MX_FRect body;
  float scale_x, scale_y;
  float rotation;
  float velocity;
  float acceleration;
} MX_PhysicsBody2D;

#endif // MX_GENERAL_PUBLIC_H
