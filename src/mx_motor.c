#include "mx_motor.h"
#include "mx_controls.h"
#include "mx_renderer.h"
#include "mx_general_internal.h"

MX_Motor_Handle create_motor() {
  struct MX_Motor *motor = (struct MX_Motor*)SDL_malloc(sizeof(struct MX_Motor));
  SDL_memset(motor, 0, sizeof(struct MX_Motor));
  motor->running = 1;
  return (MX_Motor_Handle)motor;
}

void destroy_motor(MX_Motor_Handle motor_handle) {
  struct MX_Motor *motor = (struct MX_Motor*)motor_handle;
  SDL_free(motor);
}

void run_game_loop(void* hull_handle) {
  struct MX_Hull *hull = (struct MX_Hull*)hull_handle;
  struct MX_Motor *motor = (struct MX_Motor*)hull->motor;
  
  handle_input(hull_handle);
  
  if (motor->running) {
    update_scene(hull_handle);
  }
  
  render_scene(hull_handle);
}

void end_game_loop(void *hull_handle) {
  struct MX_Hull *hull = (struct MX_Hull*)hull_handle;
  struct MX_Motor *motor = (struct MX_Motor*)hull->motor;
  motor->running = 0;
}

Uint64 is_running(void *hull_handle) {
  struct MX_Hull *hull = (struct MX_Hull*)hull_handle;
  struct MX_Motor *motor = (struct MX_Motor*)hull->motor;
  return motor->running;
}