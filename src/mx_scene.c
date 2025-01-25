#include "../include/mx_scene.h"
#include "mx_scene_internal.h"
#include "mx_general_internal.h"

void create_scene_manager(void) {
  //MX_SceneManager *manager = (MX_SceneManager*)SDL_malloc(sizeof(MX_SceneManager));
  //if (!manager) {
  //  SDL_Log("Failed to allocate memory for MX_SceneManager");
  //  return NULL;
  //}
  //SDL_memset(manager, 0, sizeof(MX_SceneManager));
  
  //void *new_scene_instance = SDL_malloc(sizeof(Scene));
  //if (!new_scene_instance) {
  //  SDL_Log("Failed to allocate memory for initial scene");
  //  SDL_free(manager);
  //  return NULL;
  //}
  
  //SDL_memset(new_scene_instance, 0, sizeof(Scene));
  //splash_scene_setup(new_scene_instance);
  //((Scene*)new_scene_instance)->state = SCENE_STATE_TRANSITIONING_IN;
  
  //manager->transitioning = 0;
  //manager->transition_progress = 0;
  //manager->next_scene = new_scene_instance;
  
  //return (void*)manager;
}

void destroy_scene_manager(void *scene_manager_pointer) {
  //MX_SceneManager *manager = (MX_SceneManager*)scene_manager_pointer;
  
  //if (manager->current_scene) {
  //  if (((Scene*)manager->current_scene)->cleanup) {
  //    ((Scene*)manager->current_scene)->cleanup(manager->current_scene);
  //  }
  //  SDL_free(manager->current_scene);
  //}
  
  //if (manager->next_scene) {
  //  if (((Scene*)manager->next_scene)->cleanup) {
  //    ((Scene*)manager->next_scene)->cleanup(manager->next_scene);
  //  }
  //  SDL_free(manager->next_scene);
  //}
  
  //SDL_free(manager);
}

void transition_to_scene(void *hull_pointer, Uint64 new_scene) {
  //Hull *hull = (Hull*)hull_pointer;
  //MX_SceneManager *manager = (MX_SceneManager*)hull->navigation;
  
  //if (manager->transitioning) {
  //  SDL_Log("Scene transition already in progress");
  //  return;
  //}
  
  //Scene *new_scene_instance = (Scene*)SDL_malloc(sizeof(Scene));
  //if (!new_scene_instance) {
  //  SDL_Log("Failed to allocate memory for new scene");
  //  return;
  //}
  
  //SDL_memset(new_scene_instance, 0, sizeof(Scene));
  
  //switch ((SceneType)new_scene) {
  //  case SCENE_SPLASH:
  //    splash_scene_setup(new_scene_instance);
  //    break;
  //  case SCENE_MENU:
  //    menu_scene_setup(new_scene_instance);
  //    break;
  //  case SCENE_GAME:
  //    game_scene_setup(new_scene_instance);
  //    break;
  //  default:
  //    SDL_Log("Invalid scene type requested");
  //    SDL_free(new_scene_instance);
  //    return;
  //}
  
  //if (manager->current_scene) {
  //  ((Scene*)manager->current_scene)->state = SCENE_STATE_TRANSITIONING_OUT;
  //}
  //new_scene_instance->state = SCENE_STATE_TRANSITIONING_IN;
  
  //manager->transitioning = 1;
  //manager->transition_progress = 0;
  //manager->next_scene = new_scene_instance;
  
  //if (new_scene_instance->initialize) {
  //  new_scene_instance->initialize(hull_pointer);
  //}
}

void update_scene(void *hull_pointer) {
  //Hull *hull = (Hull*)hull_pointer;
  //MX_SceneManager *manager = ((MX_SceneManager*)(hull->navigation));
  
  //if (manager->transitioning) {
  //  manager->transition_progress += 1;
  //  SDL_Log("Transition progress: %d", manager->transition_progress);
    
  //  if (manager->transition_progress >= 100) {
  //    SDL_Log("Completing transition");
  //    Scene *old_scene = (Scene*)manager->current_scene;
  //    Scene *new_scene = (Scene*)manager->next_scene;
      
      // Ensure clean state transitions
  //    if (old_scene) {
  //      SDL_Log("Cleaning up current scene: %p", manager->current_scene);
  //      if (old_scene->cleanup) {
  //        old_scene->cleanup(hull_pointer);
  //      }
  //      SDL_free(old_scene);
  //      SDL_Log("Current scene cleaned up");
  //    }
      
  //    if (new_scene) {
  //      SDL_Log("Setting current scene to new scene");
  //      manager->current_scene = new_scene;
  //      new_scene->state = SCENE_STATE_ACTIVE;
  //    }
      
  //    manager->next_scene = NULL;
  //    manager->transitioning = 0;
  //    manager->transition_progress = 0;
  //  }
  //}
  
  //if (manager->current_scene && 
  //    ((Scene*)manager->current_scene)->state == SCENE_STATE_ACTIVE &&
  //    ((Scene*)manager->current_scene)->update) {
  //  ((Scene*)manager->current_scene)->update(hull_pointer);
  //}
}

void render_scene(void *hull_pointer) {
  //Hull *hull = (Hull*)hull_pointer;
  //MX_SceneManager *manager = (MX_SceneManager*)hull->navigation;
  
  //if (manager->transitioning) {
  //  if (manager->current_scene && ((Scene*)manager->current_scene)->render) {
  //    ((Scene*)manager->current_scene)->render(hull_pointer);
  //  }
  //  if (manager->next_scene && ((Scene*)manager->next_scene)->render) {
  //    ((Scene*)manager->next_scene)->render(hull_pointer);
  //  }
  //} else {
  //  if (manager->current_scene && ((Scene*)manager->current_scene)->render) {
  //    ((Scene*)manager->current_scene)->render(hull_pointer);
  //  }
  //}
}