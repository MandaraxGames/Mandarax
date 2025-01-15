#include "mx_motor.h"
#include "mx_controls.h"
#include "mx_renderer.h"
#include "mx_general_internal.h"

MX_Motor_Handle create_motor() {
  MX_Motor *motor = (MX_Motor*)SDL_malloc(sizeof(MX_Motor));
  SDL_memset(motor, 0, sizeof(MX_Motor)); // sets all values to zero,
  motor->running = SDL_TRUE; // only running needs a default value not equal to zero
  return (MX_Motor_Handle)motor;
}

void destroy_motor(MX_Motor_Handle motor_handle) {
  MX_Motor *motor = (MX_Motor*)motor_handle;
  SDL_free(motor);
}

void end_game_loop(MX_Hull_Handle hull_handle) {
  MX_Hull *hull = (MX_Hull*)hull_handle;
  MX_Motor *motor = (MX_Motor*)hull->motor;
  motor->running = SDL_FALSE;
}

Uint64 is_running(MX_Hull_Handle hull_handle) {
  MX_Hull *hull = (MX_Hull*)hull_handle;
  MX_Motor *motor = (MX_Motor*)hull->motor;
  return motor->running;
}

void run_game_loop(MX_Hull_Handle hull_handle, void (*update)(float delta_ms)) {
  MX_Hull *hull = (MX_Hull*)hull_handle;
  MX_Motor *motor = (MX_Motor*)hull->motor;
  while (is_running(hull_handle)) {
    motor->current_time = SDL_GetTicks64();
    float frame_time = motor->current_time - motor->previous_time;
    motor->previous_time = motor->current_time;
    motor->accumulated_time += frame_time;
    float update_count = 0;
    //while (SDL_PollEvent(&event)) {
    //  switch (event.type) {
    //    case SDL_QUIT:
    //      end_game_loop(hull_handle);
    //      return;

    //    default:
    //      break;
    //  }
    //}
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