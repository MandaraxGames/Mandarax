# Dynamic Hull Configuration Design

## Project Context
- Building a configurable game engine where users can specify which systems they need
- Using opaque pointers for clean API boundaries
- Supporting runtime configuration of game systems

## Configuration System

### Flags and Options
```c
typedef enum {
    MX_HULL_REQUIRED     = 0x0001,  // Window + Motor (minimum)
    MX_HULL_RENDERER     = 0x0002,  // Basic renderer
    MX_HULL_RENDERER_3D  = 0x0004,  // 3D renderer
    MX_HULL_MANIFEST     = 0x0008,  // Basic entity system
    MX_HULL_MANIFEST_ECS = 0x0010,  // ECS-style entity system
    MX_HULL_CONTROLS     = 0x0020,  // Input handling
    MX_HULL_NAVIGATION   = 0x0040,  // Scene management
    MX_HULL_UI           = 0x0080,  // User interface
} MxHullFlags;
```

### Configuration Structure
```c
typedef struct {
    const char* title;
    uint32_t width;
    uint32_t height;
    uint32_t flags;
    uint8_t renderer_count;   // 0-2 renderers
    uint8_t manifest_count;   // 0-2 entity systems
} HullConfig;
```

### Hull Structure
```c
typedef struct {
    SDL_Window* window;      // Required
    Motor* motor;           // Required
    
    uint8_t renderer_count;
    Renderer** renderers;    // Dynamic array
    
    uint8_t manifest_count;
    void** manifests;       // Dynamic array
    
    Controls* controls;      // Optional
    SceneManager* navigation;// Optional
    UserInterface* ui;      // Optional
} Hull;
```

## Key Features
- Runtime configuration of game systems
- Dynamic memory allocation based on needs
- Support for multiple renderers/manifests
- Clean API with opaque pointers
- Flexible system combination

## Memory Management
1. Memory allocated at runtime based on configuration
2. Systems can be added/removed during development
3. Supports dynamic reconfiguration if needed
4. Memory layout determined at runtime

## API Usage
```c
// Create configuration
HullConfig config = mx_hull_config_default();
config.flags |= MX_HULL_RENDERER_3D | MX_HULL_MANIFEST_ECS;
config.renderer_count = 1;
config.manifest_count = 1;

// Create hull
Hull* hull = mx_hull_create(&config);

// Access systems
Renderer* renderer = mx_hull_get_renderer(hull, 0);
void* ecs = mx_hull_get_manifest(hull, 0);

// Cleanup
mx_hull_destroy(hull);
```

## Tradeoffs
### Advantages
- Maximum flexibility
- Easy to modify at runtime
- No compile-time limitations
- Simple to prototype with

### Disadvantages
- Runtime overhead
- Memory fragmentation possible
- No compile-time optimizations
- Additional pointer indirection

# Static Configuration Design

## Project Context
- Compile-time configuration of game systems
- Zero overhead for unused features
- Type-safe system access
- Optimized memory layout

## Configuration System

### Component Declaration
```c
// In game_config.h
#define MX_GAME_CONFIG              \
    MX_REQUIRE_WINDOW              \
    MX_REQUIRE_MOTOR               \
    MX_USE_RENDERER(MX_RENDERER_3D) \
    MX_USE_PHYSICS(MX_PHYSICS_TYPE_RIGID_BODY)
```

### Generated Structure
```c
// Generated at compile time
typedef struct MyGame_Hull {
    mx_window window;       // Required
    mx_motor motor;        // Required
    mx_renderer_3d r3d;    // Configured
    mx_physics physics;    // Configured
} MyGame_Hull;
```

## Key Features
- Compile-time system configuration
- Zero overhead for unused features
- Direct member access to systems
- Type-safe interfaces
- Optimal memory layout

## Memory Management
1. Structure size known at compile time
2. No dynamic allocation required
3. Cache-friendly memory layout
4. No runtime configuration overhead

## API Usage
```c
// Declare game-specific hull type
MX_DECLARE_HULL(MyGame);

// Create hull instance
MyGame_Hull hull;

// Initialize
mx_init(&hull, "My Game", 800, 600);

// Direct system access
hull.renderer3d->render(scene);
hull.physics->step(delta_time);

// Cleanup
mx_cleanup(&hull);
```

## Implementation Techniques
- Preprocessor metaprogramming
- X-Macros for structure generation
- Compile-time configuration validation
- Module-based system composition

## Tradeoffs
### Advantages
- Optimal performance
- No runtime overhead
- Better cache utilization
- Type-safe interfaces
- Compile-time error checking

### Disadvantages
- More complex implementation
- Requires rebuild for configuration changes
- Advanced C knowledge required
- More sophisticated build system needed

## Future Possibilities
- Advanced AI systems
- Multiple physics types
- Various rendering backends
- Network gameplay options
- Asset streaming systems
- Scripting integration
- Terrain generation
- Particle systems
- Audio subsystems

## Migration Path
1. Start with dynamic configuration
2. Keep systems modular and independent
3. Design clean interfaces
4. Plan for static configuration
5. Gradually introduce compile-time features
6. Maintain backward compatibility