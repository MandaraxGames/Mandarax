#ifndef SCENE_H
#define SCENE_H

#include "mx_general_public.h"

void create_scene_manager(void);
void destroy_scene_manager(void *scene_manager_pointer);
void transition_to_scene(void *hull_pointer, Uint64 new_scene);
void update_scene(void *hull_pointer);
void render_scene(void *hull_pointer);

#endif // SCENE_H