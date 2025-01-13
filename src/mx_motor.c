#include <SDL_timer.h>
#include "mx_motor.h"
#include "mx_controls.h"
#include "mx_renderer.h"
#include "mx_general_internal.h"

MX_Motor_Handle create_motor() {
  struct MX_Motor *motor = (struct MX_Motor*)SDL_malloc(sizeof(struct MX_Motor));
  SDL_memset(motor, 0, sizeof(struct MX_Motor)); // sets all values to zero,
  motor->running = 1; // only running needs a default value not equal to zero
  return (MX_Motor_Handle)motor;
}

void destroy_motor(MX_Motor_Handle motor_handle) {
  struct MX_Motor *motor = (struct MX_Motor*)motor_handle;
  SDL_free(motor);
}

void run_game_loop(MX_Hull_Handle hull_handle, void (*update)(Uint64 delta_ms)) {
  if (motor->running) {
    struct MX_Hull *hull = (struct MX_Hull*)hull_handle;
    struct MX_Motor *motor = (struct MX_Motor*)hull->motor;
    
    motor->current_time = SDL_GetTicks64();
    Uint64 frame_time = motor->current_time - motor->previous_time;
    motor->previous_time = motor->current_time;
    motor->accumulated_time += frame_time;
    Uint64 update_count = 0;
    
    handle_input(hull_handle);
    
    while (motor->accumulated_time >= FIXED_DELTA && update_count < MAX_STEPS_PER_UPDATE) {
      update(FIXED_DELTA);   // Game logic at fixed time step
      perform_rendering(hull_handle);
      motor->accumulated_time -= FIXED_DELTA;
      update_count++;
    }
    
    // If we hit max steps, we're running too slow - adjust accumulator
    if (update_count >= MAX_STEPS_PER_UPDATE) {
      motor->accumulated_time = 0;
    }
  }
}

void end_game_loop(MX_Hull_Handle hull_handle) {
  struct MX_Hull *hull = (struct MX_Hull*)hull_handle;
  struct MX_Motor *motor = (struct MX_Motor*)hull->motor;
  motor->running = 0;
}

Uint64 is_running(MX_Hull_Handle hull_handle) {
  struct MX_Hull *hull = (struct MX_Hull*)hull_handle;
  struct MX_Motor *motor = (struct MX_Motor*)hull->motor;
  return motor->running;
}