#ifndef MX_GENERAL_INTERNAL_H
#define MX_GENERAL_INTERNAL_H

#include "mx_general_public.h"

// State Enums
typedef enum {
  MX_SCENE_STATE_IDLE,
  MX_SCENE_STATE_TRANSITIONING_IN,
  MX_SCENE_STATE_ACTIVE,
  MX_SCENE_STATE_TRANSITIONING_OUT
} MX_SceneState;

#ifdef _MSC_VER
  #pragma pack(push, 1)
#endif

typedef struct {
#ifndef _MSC_VER
  __attribute__((packed))
#endif
  SDL_bool is_free;
  Uint32 size;
  char data[BLOCK_SIZE - sizeof(SDL_bool) - sizeof(Uint32)];
} MX_PoolBlock;

#ifdef _MSC_VER
  #pragma pack(pop)
#endif

typedef struct {
  Uint32 free_blocks;
  MX_PoolBlock blocks[NUM_BLOCKS];
} MX_PoolManager;

typedef struct {
  Uint64 id;
  char name[32];
  Uint32 type;
  Uint32 mask;            // Bit mask of which components exist
  Uint8 comp_to_index[MAX_ENTITY_COMPONENTS];  // Fixed lookup array - O(1) access
  Uint8 capacity;             // Allocated size of components array
  Uint8 count;                // Number of components currently in use
  void (*update)(MX_Entity_Handle entity_handle, float delta_ms);
  void** components;         // Dynamic array of components
} MX_Entity;

typedef struct {
  Uint64 element_size;
  Uint64 max_elements;
  Uint64 top;
  void* data;
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
  MX_Stack_Handle text_stack;
  SDL_Texture* texture;
} MX_CachedText;

typedef struct {
  MX_Stack_Handle input_stack;
  SDL_Event event;
} MX_Controls;

typedef struct {
  Uint64 mod_count;
  Uint64 max_modifications;
  SDL_Renderer* context;
  MX_RenderFunction* render_modifications;
} MX_Renderer;

typedef struct {
  Uint64 entity_count;
  Uint64 max_entities;  // User-defined max
  void (*update)(void* manifest);
  void (*render)(void* manifest, SDL_Renderer* context);
  void** entities;      // Dynamic array of entities
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
  MX_Hull_Flags flags;
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