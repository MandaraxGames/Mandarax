#include "mx_motor.h"
#include "mx_controls.h"
#include "mx_renderer.h"
#include "mx_general_internal.h"

void *create_motor() {
  Motor *motor = (Motor*)SDL_malloc(sizeof(Motor));
  SDL_memset(motor, 0, sizeof(Motor));
  motor->running = 1;
  return (void*)motor;
}

void destroy_motor(void *motor_pointer) {
  Motor *motor = (Motor*)motor_pointer;
  SDL_free(motor);
}

void run_game_loop(void* hull_pointer) {
  Hull *hull = (Hull*)hull_pointer;
  Motor *motor = (Motor*)hull->motor;
  
  handle_input(hull_pointer);
  
  if (motor->running) {
    update_scene(hull_pointer);
  }
  
  render_scene(hull_pointer);
}

void end_game_loop(void *hull_pointer) {
  Hull *hull = (Hull*)hull_pointer;
  Motor *motor = (Motor*)hull->motor;
  motor->running = 0;
}

Uint64 is_running(void *hull_pointer) {
  Hull *hull = (Hull*)hull_pointer;
  Motor *motor = (Motor*)hull->motor;
  return motor->running;
}