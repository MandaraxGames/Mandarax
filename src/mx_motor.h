#ifndef MOTOR_H
#define MOTOR_H

#include "mx_common.h"

typedef struct MX_Motor* MX_Motor_Handle;

MX_Motor_Handle create_motor(void);
void destroy_motor(MX_Motor_Handle motor_pointer);
void run_game_loop(void *hull_pointer, void (*update)(Uint64 delta_ms));
void toggle_pause(void *hull_pointer);
void end_game_loop(void *hull_pointer);
Uint64 is_running(void *hull_pointer);
void reset_game(void* hull_pointer);

#endif // MOTOR_H

