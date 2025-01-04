#ifndef GENERAL_INTERNAL_H
#define GENERAL_INTERNAL_H

#include "common.h"

#define MAX_MODIFICATIONS 10
#define MAX_ENEMIES 10
#define MAX_WORD_LENGTH 20
#define MAX_TYPOS 10
#define MAX_STACK_SIZE (MAX_WORD_LENGTH + MAX_TYPOS)
#define FEEDBACK_DURATION_MS 500

extern TTF_Font* font;

typedef enum {
  GAME_STATE_PLAYING,
  GAME_STATE_PAUSED,
  GAME_STATE_OVER
} GameState;

typedef enum {
  SCENE_SPLASH,
  SCENE_MENU, 
  SCENE_GAME,
  SCENE_PAUSE
} SceneType;

typedef enum {
  SCENE_STATE_IDLE,
  SCENE_STATE_TRANSITIONING_IN,
  SCENE_STATE_ACTIVE,
  SCENE_STATE_TRANSITIONING_OUT
} SceneState;

typedef struct {
  Uint64 end;
  Uint64 top;
  char stack[MAX_STACK_SIZE];
} Stack;

typedef struct {
  Uint64 width;
  Uint64 height;
  SDL_Texture* texture;
  Stack* word_stack;
} CachedText;

typedef struct {
  Sint64 x, y;
  Uint64 start_time;
  Uint64 duration;
  SDL_Color color;
} TypeFeedback;

typedef struct {
  Sint64 x, y;
  Uint64 speed;
  Uint64 active;
  void *cached_text;
} Enemy;

typedef struct {
  Uint64 enemies_left;
  Uint64 leading_enemy_index;
  void *typing_stack;
  Enemy enemies[MAX_ENEMIES];
} Enemies;

typedef struct {
  SDL_Event event;
  void *input_stack;
} Controls;

typedef struct {
  SDL_Renderer *renderer;
  Sint64 mod_count;
  void (*render_modifications[MAX_MODIFICATIONS])(SDL_Renderer *);
} Renderer;

typedef struct {
  Uint64 running;
} Motor;

typedef struct {
  Uint64 message_start_time;
  Uint64 message_duration;
  char message[256];
  TypeFeedback feedback;
} UserInterface; // Overlay

typedef struct {
  SceneType type;
  SceneState state;  // Add state tracking
  void (*initialize)(void *hull_pointer);
  void (*update)(void *hull_pointer);
  void (*render)(void *hull_pointer);
  void (*cleanup)(void *hull_pointer);
} Scene; // Manuevers. e.x. takeoff, landing, plaentary orbit and normal flight

typedef struct {
  Uint64 transitioning;
  Sint64 transition_progress;
  void *current_scene;
  void *next_scene;
} SceneManager; // Guidance / Navigation system

typedef struct {
  SDL_Window *window;
  void *controls;
  void *renderer;
  void *motor;
  void *manifests; // Pointer to Struct, which acts like an entity manager (enemy)
  void *ui;
  void *navigation; // SceneManager
} Hull;

#endif // GENERAL_INTERNAL_H

