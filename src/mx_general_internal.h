#ifndef MX_GENERAL_INTERNAL_H
#define MX_GENERAL_INTERNAL_H

#include <SDL.h>
#include <SDL_stdinc.h>
//#include <SDL_timer.h>
//#include <SDL_ttf.h>
//#include <SDL_image.h>

typedef enum {
    MX_HULL_REQUIRED     = 0x0001,  // Window + Motor + Renderer (minimum)
    MX_HULL_RENDERER     = 0x0002,  // Additional renderers
    MX_HULL_MANIFEST     = 0x0008,  // Entity systems
    MX_HULL_CONTROLS     = 0x0010,  // Input handling
    MX_HULL_NAVIGATION   = 0x0020,  // Scene management
    MX_HULL_UI           = 0x0040,  // User interface
} MX_HullFlags;

typedef enum {
    MX_SCENE_STATE_IDLE,
    MX_SCENE_STATE_TRANSITIONING_IN,
    MX_SCENE_STATE_ACTIVE,
    MX_SCENE_STATE_TRANSITIONING_OUT
} MX_SceneState;

#ifdef _MSC_VER
    #pragma pack(push, 1)
#endif

struct pool_block {
#ifndef _MSC_VER
    __attribute__((packed))
#endif
    SDL_Bool is_free;
    Uint32 size;
    char data[BLOCK_SIZE - sizeof(SDL_Bool) - sizeof(Uint32)];
};

#ifdef _MSC_VER
    #pragma pack(pop)
#endif

struct pool_manager {
    struct pool_block blocks[NUM_BLOCKS];
    Uint32 free_blocks;
};

typedef struct {
  void* data;
  Uint64 element_size;
  Uint64 max_elements;
  Uint64 top;
} MX_Stack;

typedef struct MX_State {
  MX_PushdownAutomata_Handle parent; // Points to parent state/manager
  MX_Stack_Handle states;            // Stack of sub-states
  void* context;               // State-specific data
} MX_State;

typedef struct {
  MX_Stack_Handle states;     // Root level state stack
  void* context;        // Global context data
} MX_PushdownAutomata;

typedef struct {
  Uint64 width;
  Uint64 height;
  SDL_Texture* texture;
  MX_Stack_Handle text_stack;
} MX_CachedText;

typedef struct {
  SDL_Event event;
  MX_Stack_Handle input_stack;
} MX_Controls;

typedef struct {
  SDL_Renderer* renderer;
  Sint64 mod_count;
  Sint64 max_modifications;
  MX_RenderFunction* render_modifications;
} MX_Renderer;

typedef struct {
  Uint64 entity_count;
  Uint64 max_entities;  // User-defined max
  void** entities;      // Dynamic array of entities
  void (*update)(void* manifest);
  void (*render)(void* manifest, SDL_Renderer* renderer);
} MX_Manifest;

typedef struct {
  SDL_bool running;
  float current_time;     // In milliseconds
  float previous_time;    // In milliseconds
  float accumulated_time; // In milliseconds
} MX_Motor;

typedef struct {
  MX_SceneState state;
  void (*initialize)(MX_Hull_Handle hull_pointer);
  void (*update)(MX_Hull_Handle hull_pointer);
  void (*render)(MX_Hull_Handle hull_pointer);
  void (*cleanup)(MX_Hull_Handle hull_pointer);
} MX_Scene;

typedef struct {
  Uint64 transitioning;
  Sint64 transition_progress;
  void* current_scene;
  void* next_scene;
} MX_SceneManager;

typedef struct {
  // Required components
  SDL_Window* window;
  MX_Motor_Handle motor;
  MX_Renderer_Handle renderer;    // Required primary renderer
  
  // Optional entity systems (MX_HULL_MANIFEST)
  // Uint8 manifest_count;
  // Manifest** manifests;  // Array of entity systems
  
  // Optional systems
  // Controls* controls;    // MX_HULL_CONTROLS
  // SceneManager* navigation;  // MX_HULL_NAVIGATION
  // void* ui;             // MX_HULL_UI
} MX_Hull;

#endif // MX_GENERAL_INTERNAL_H