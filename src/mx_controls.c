#include "mx_controls.h"
#include "mx_controls_internal.h"
#include "mx_stack.h"
#include "mx_stack_internal.h"
#include "mx_motor.h"
#include "mx_motor_internal.h"
#include "mx_general_internal.h"

int is_specific_key(SDL_Keycode key);

void *create_controls(void) {
  MX_Controls *controls = (MX_Controls*)SDL_malloc(sizeof(MX_Controls));
  SDL_memset(controls, 0, sizeof(MX_Controls));
  //controls->input_stack = create_stack(sizeof(char), max_length);
    
  return (void*)controls;
}

void destroy_controls(void *controls_pointer) {
  MX_Controls *controls = (MX_Controls*)controls_pointer;
    
  if (controls->input_stack) {
    destroy_stack((MX_Stack_Handle)controls->input_stack);
  }
    
  SDL_free(controls);
}

void handle_input(void *hull_pointer) {
  //MX_Hull *hull = (MX_Hull*)hull_pointer;
  //MX_Controls *controls = (MX_Controls*)(hull->controls);

  //while (SDL_PollEvent(&controls->event)) {
  //  switch (controls->event.type) {
  //    case SDL_KEYDOWN: {
  //      SDL_Keycode key = controls->event.key.keysym.sym;
  //      SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "%c : key down", key);

  //      switch(key) {
  //        case SDLK_ESCAPE:
  //          break;

  //        case SDLK_RETURN:
  //          break;

  //        default:
  //          if ((GameState)get_game_state() == GAME_STATE_PLAYING && is_specific_key(key)) {
  //            Uint64 err = push_on_stack((MX_Stack_Handle)controls->input_stack, (char)key);
  //            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "pushed char %c with error %i", key, err);
  //          }
  //          break;
  //      }
  //      break;
  //    }

  //    case SDL_MOUSEBUTTONUP: {
  //      int x, y;
  //      SDL_GetMouseState(&x, &y);
  //      break;
  //    }
  //  }
  //}
}

int is_specific_key(SDL_Keycode key) {
  return ((key >= SDLK_a && key <= SDLK_z) ||
          (key >= SDLK_0 && key <= SDLK_9) ||
          key == SDLK_SPACE ||
          key == SDLK_RETURN ||
          key == SDLK_BACKSPACE ||
          key == SDLK_TAB);
}