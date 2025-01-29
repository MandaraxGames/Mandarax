#include "mx_hull.h"
#include "mx_hull_internal.h"
#include "mx_motor.h"
#include "mx_motor_internal.h"
#include "mx_controls.h"
#include "mx_controls_internal.h"
#include "mx_renderer.h"
#include "mx_renderer_internal.h"
#include "mx_scene.h"
#include "mx_scene_internal.h"
#include "mx_general_internal.h"

int _fltused = 0;

MX_Hull_Handle assemble_app(const char* title, Uint64 width, Uint64 height, MX_Hull_Flags flags) {
  if (flags &  MX_HULL_FONT_RENDERER) {
    TTF_Init();
  }
  
  if (flags &  MX_HULL_IMAGE_RENDERER) {
    Sint64 img_flags = IMG_INIT_PNG;
    Sint64 img_initted = IMG_Init(img_flags);
    if((img_initted & img_flags) != img_flags) {
      SDL_Log("SDL_image init failed: %s\n", IMG_GetError());
      return NULL;
    }
    SDL_Log("SDL_image initialized successfully");
  }
  
  MX_Hull* hull = (MX_Hull*)SDL_malloc(sizeof(MX_Hull));
  if (!hull) {
    return NULL;
  }
  SDL_memset(hull, 0, sizeof(MX_Hull));
  
  hull->flags = flags;
  hull->window = SDL_CreateWindow(title,
                                  SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED,
                                  width,
                                  height,
                                  SDL_WINDOW_SHOWN);
  hull->renderer = create_renderer(SDL_CreateRenderer(hull->window, -1, SDL_RENDERER_ACCELERATED));
  hull->motor = create_motor();
  //hull->controls = create_controls();
  //hull->manifests = create_all_enemies();
  //hull->ui = create_ui();
  //hull->navigation = create_scene_manager();
  
  //transition_to_scene((void*)hull, SCENE_SPLASH);
  
  // Add render modifications
  // should be handled better probably as an inital part of renderer creation / intitialization
  add_render_modification((MX_Hull_Handle)hull, render_grid);  
  //add_render_modification(hull, render_all_enemies);
  //add_render_modification(hull, render_ui);
  
  char base_path[256];
  SDL_GetBasePath();
  SDL_Log("Base Path is: %s", SDL_GetBasePath());
  
  return (MX_Hull_Handle)hull;
}

void disassemble_app(MX_Hull_Handle hull_handle) {
  MX_Hull* hull = (MX_Hull*)hull_handle;
  if (!hull) return;
  //TTF_CloseFont(font);
  //TTF_Quit();
  //IMG_Quit();
  //destroy_controls(hull->controls);
  destroy_renderer(hull->renderer);
  destroy_motor(hull->motor);
  //if (hull->manifests) {
  //  cleanup_enemies(hull->manifests);
  //}
  //destroy_ui(hull->ui);
  SDL_DestroyWindow(hull->window);
  SDL_free(hull);
}

void render_grid(SDL_Renderer* renderer) {
  if (!renderer) return;
  int cell_size = 64;
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

  for (int i = 0; i < SCREEN_WIDTH / cell_size; i++) {
    SDL_RenderDrawLine(renderer, i * cell_size, 0, i * cell_size, SCREEN_HEIGHT);
    for (int j = 0; j < SCREEN_HEIGHT / cell_size; j++) {
      SDL_RenderDrawLine(renderer, 0, j * cell_size, SCREEN_WIDTH, j * cell_size);
    }
  }
}