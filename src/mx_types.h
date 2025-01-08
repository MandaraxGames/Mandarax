#ifndef MX_TYPES_H
#define MX_TYPES_H

#include "mx_common.h"

typedef enum {
    MX_HULL_REQUIRED     = 0x0001,  // Window + Motor + Renderer (minimum)
    MX_HULL_RENDERER     = 0x0002,  // Additional renderers
    MX_HULL_MANIFEST     = 0x0008,  // Entity systems
    MX_HULL_CONTROLS     = 0x0010,  // Input handling
    MX_HULL_NAVIGATION   = 0x0020,  // Scene management
    MX_HULL_UI           = 0x0040,  // User interface
} MxHullFlags;

typedef enum {
    MX_SCENE_STATE_IDLE,
    MX_SCENE_STATE_TRANSITIONING_IN,
    MX_SCENE_STATE_ACTIVE,
    MX_SCENE_STATE_TRANSITIONING_OUT
} MxSceneState;

typedef struct {
    const char* title;
    Uint32 width;
    Uint32 height;
    Uint32 flags;          // Configuration flags
    Uint8 renderer_count;  // Number of additional renderers
    Uint8 manifest_count;  // Number of entity systems
} MxConfig;

#endif // MX_TYPES_H