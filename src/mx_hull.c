#include "mx_hull.h"
#include "mx_controls.h"
#include "mx_renderer.h"
#include "mx_motor.h"
#include "mx_scene.h"
#include "mx_general_internal.h"

MX_Hull_Handle assemble_app(const char* title, Uint64 width, Uint64 height, MX_Render_Modification game_render) {
    
  //TTF_Init();
  //Sint64 img_flags = IMG_INIT_PNG;
  //Sint64 img_initted = IMG_Init(img_flags);
  //if((img_initted & img_flags) != img_flags) {
  //  SDL_Log("SDL_image init failed: %s\n", IMG_GetError());
  //  return NULL;
  //}
  //SDL_Log("SDL_image initialized successfully");
    
  struct MX_Hull* hull = (MX_Hull*)SDL_malloc(sizeof(MX_Hull));
  if (!hull) {
      return NULL;
  }
  SDL_memset(hull, 0, sizeof(MX_Hull));
  
  hull->window = SDL_CreateWindow(title,
                                  SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED,
                                  width,
                                  height,
                                  SDL_WINDOW_SHOWN);
  // hull->controls = create_controls();
  hull->renderer = create_renderer(SDL_CreateRenderer(hull->window, -1, SDL_RENDERER_ACCELERATED));
  hull->motor = create_motor();
  //hull->manifests = create_all_enemies();
  //hull->ui = create_ui();
  //hull->navigation = create_scene_manager();
  
  
  //transition_to_scene((void*)hull, SCENE_SPLASH);
  
  // Add render modifications
  // should be handled better probably as an inital part of renderer creation / intitialization
  add_render_modification((MX_Hull_Handle)hull, render_grid);  
  //add_render_modification(hull, render_all_enemies);
  //add_render_modification(hull, render_ui);
  add_render_modification((MX_Hull_Handle)hull, game_render);  // Game rendering
  
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

void render_grid(MX_Hull_Handle hull_handle) {
  MX_Hull* hull = (MX_Hull*)hull_handle;
  if (!hull || !hull->renderer) return;
  
  SDL_Renderer* renderer = ((MX_Renderer*)hull->renderer)->renderer;
  int cell_size = 64;
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

  for (int i = 0; i < SCREEN_WIDTH / cell_size; i++) {
    SDL_RenderDrawLine(renderer, i * cell_size, 0, i * cell_size, SCREEN_HEIGHT);
    for (int j = 0; j < SCREEN_HEIGHT / cell_size; j++) {
      SDL_RenderDrawLine(renderer, 0, j * cell_size, SCREEN_WIDTH, j * cell_size);
    }
  }
}