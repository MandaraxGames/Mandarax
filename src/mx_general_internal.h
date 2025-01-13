#ifndef GENERAL_INTERNAL_H
#define GENERAL_INTERNAL_H

#include "mx_common.h"
#include "mx_types.h"

typedef struct {
  void* data;
  Uint64 element_size;
  Uint64 max_elements;
  Uint64 top;
} MX_Stack;

typedef struct {
  Uint64 width;
  Uint64 height;
  SDL_Texture* texture;
  Stack* text_stack;
} MX_CachedText;

typedef struct {
  SDL_Renderer* renderer;
  Sint64 mod_count;
  Sint64 max_modifications;
  void (**render_modifications)(SDL_Renderer*);
} MX_Renderer;

typedef struct {
  Uint64 entity_count;
  Uint64 max_entities;  // User-defined max
  void** entities;      // Dynamic array of entities
  void (*update)(void* manifest);
  void (*render)(void* manifest, SDL_Renderer* renderer);
} MX_Manifest;

typedef struct {
  Uint64 running;
  Uint64 current_time;     // In milliseconds
  Uint64 previous_time;    // In milliseconds
  Uint64 accumulated_time; // In milliseconds
} MX_Motor;

typedef struct {
  MxSceneState state;
  void (*initialize)(void* hull_pointer);
  void (*update)(void* hull_pointer);
  void (*render)(void* hull_pointer);
  void (*cleanup)(void* hull_pointer);
} MX_Scene;

typedef struct {
  Uint64 transitioning;
  Sint64 transition_progress;
  void* current_scene;
  void* next_scene;
} MX_SceneManager;

// Main hull structure reflecting mx_types.h configuration
struct MX_Hull {
  // Required components
  SDL_Window* window;
  MX_Motor* motor;
  MX_Renderer* renderer;    // Required primary renderer
  
  // Optional entity systems (MX_HULL_MANIFEST)
  // Uint8 manifest_count;
  // Manifest** manifests;  // Array of entity systems
  
  // Optional systems
  // Controls* controls;    // MX_HULL_CONTROLS
  // SceneManager* navigation;  // MX_HULL_NAVIGATION
  // void* ui;             // MX_HULL_UI
};

#endif // GENERAL_INTERNAL_H