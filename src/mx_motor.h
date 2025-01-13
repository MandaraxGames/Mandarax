#ifndef MOTOR_H
#define MOTOR_H

#include "mx_general_public.h"

MX_Motor_Handle create_motor(void);
void destroy_motor(MX_Motor_Handle motor_pointer);
void run_game_loop(MX_Hull_Handle hull_pointer, void (*update)(Uint64 delta_ms));
void toggle_pause(MX_Hull_Handle hull_pointer);
void end_game_loop(MX_Hull_Handle hull_pointer);
Uint64 is_running(MX_Hull_Handle hull_pointer);
void reset_game(MX_Hull_Handle hull_pointer);

#endif // MOTOR_H

