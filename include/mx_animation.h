#ifndef MX_ANIMATION_H
#define MX_ANIMATION_H

#include "mx_general_public.h"

MX_Animation* create_animation(); // Initialize with spritesheet and parameters
void set_animation_frames(Uint64 rows, Uint64 cols, Uint64 count);
void destroy_animation(MX_Animation* animation);
void play_animation(MX_Animation* animation, char* name);
void pause_animation(MX_Animation* animation, char* name);
void stop_animation(MX_Animation* animation, char* name);
void reset_animation(MX_Animation* animation, char* name);
void update_animation(MX_Animation* animation, char* name); / Handle timing and frame advancement
void set_frame(); // Jump to specific frame
void calculate_frame_rect(); // Helper to compute source rectangle
void set_animation_speed(double duration); // Modify total duration
void set_frame_speed(Uint64 frame_number, double duration); // Modify frame duration
void set_animation_loop(); // Configure loop behavior

#endif  // MX_ANIMATION_H