#ifndef MOTOR_H
#define MOTOR_H

#include "common.h"

void *create_motor(void);
void destroy_motor(void *motor_pointer);
void run_game_loop(void *hull_pointer);
void toggle_pause(void *hull_pointer);
void end_game_loop(void *hull_pointer);
Uint64 is_running(void *hull_pointer);
void reset_game(void* hull_pointer);

#endif // MOTOR_H

