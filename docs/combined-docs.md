# Mandarax Game Engine Documentation

## Project Overview
- Building a game engine called "Mandarax" (named after the computer from Vonnegut's Galápagos)
- Planning to eventually establish Mandarax Studios/Games as a company
- Using LLMs to assist in development and learning process
- Focus on cross-platform development in C
- Interest in memory-efficient design patterns

## Engine Architecture

### Core Design Philosophy
- Start flat and simple
- Create modules only when needed
- Keep related .c and .h files together
- Allow internal coupling where practical
- Support both dynamic and static configuration options

### Repository Structure
- Simple repository name: `mandarax` (without "-engine" suffix)
- Following successful examples like Godot, Raylib, etc.
- Repository URL structure: `github.com/mandaraxgames/mandarax`

```
mandarax/
  src/
    # Core files stay flat
    mx_types.h     # Basic types
    mx_core.c
    mx_core.h
    mx_memory.c
    mx_memory.h
    mx_renderer.c
    mx_renderer.h
    
    # Only create modules when multiple related files exist
    units/         # Example of when to make a module
      mx_unit.c
      mx_unit.h
      mx_ai.c
      mx_ai.h
```

### Naming Conventions
- Adopted C-style naming convention using short prefixes
- Chosen prefix: `mx_` for Mandarax
- Examples:
  ```c
  mx_window_create()
  mx_renderer_init()
  mx_entity_spawn()
  ```

## Technical Implementation

### Memory Management and Structure Design

#### Struct Packing
- Organizing struct members to minimize memory waste from padding
- Ensuring efficient memory access and alignment
- Making conscious decisions about memory layout

```c
// Bad memory layout
struct BadPacking {
    char a;     // 1 byte
    double b;   // 8 bytes (7 bytes padding added before)
    char c;     // 1 byte (7 bytes padding added after)
}; // 24 bytes total

// Better memory layout
struct BetterPacking {
    double b;   // 8 bytes
    char a;     // 1 byte
    char c;     // 1 byte
    // 6 bytes padding at end
}; // 16 bytes total
```

#### Opaque Pointers and Handle Pattern
##### Traditional Opaque Pointer
```c
// Public header (hull.h)
typedef struct Hull Hull;  // Only declaration
void* assemble_app(const char* title, uint64_t width, uint64_t height);

// Internal header (hull_internal.h)
struct Hull {
    SDL_Window* window;
    void* controls;
    void* renderer;
    // etc...
};
```

##### Single Memory Block Approach
```c
// Define sizes and offsets
#define CONTROLS_SIZE sizeof(Controls)
#define RENDERER_SIZE sizeof(Renderer)
#define TOTAL_SIZE (CONTROLS_SIZE + RENDERER_SIZE + /* etc */)

// Allocate single block
uint8_t* hull = malloc(TOTAL_SIZE);

// Access components via offsets
#define GET_CONTROLS(base) ((Controls*)((uint8_t*)base + CONTROLS_OFFSET))
```

### Configuration Systems

#### Dynamic Hull Configuration
##### Flags and Options
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

##### Configuration Structure
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

##### Hull Structure
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

#### Static Configuration
##### Component Declaration
```c
// In game_config.h
#define MX_GAME_CONFIG              \
    MX_REQUIRE_WINDOW              \
    MX_REQUIRE_MOTOR               \
    MX_USE_RENDERER(MX_RENDERER_3D) \
    MX_USE_PHYSICS(MX_PHYSICS_TYPE_RIGID_BODY)
```

##### Generated Structure
```c
// Generated at compile time
typedef struct MyGame_Hull {
    mx_window window;       // Required
    mx_motor motor;        // Required
    mx_renderer_3d r3d;    // Configured
    mx_physics physics;    // Configured
} MyGame_Hull;
```

### Engine and Game Integration

#### Repository Setup
Using Git submodules for game projects:
```bash
# Create game repo
mkdir my_game
cd my_game
git init
git submodule add https://github.com/you/mandarax.git
```

#### Engine API Design
```c
// Engine API example
typedef struct {
    const char* title;
    int width;
    int height;
    mx_init_fn on_init;
    mx_update_fn on_update;
    mx_fixed_update_fn on_fixed_update;
    float fixed_timestep;
} mx_app_config_t;
```

The engine provides:
- Core application lifecycle
- Entity management
- Physics system
- Rendering system
- Fixed/variable timestep updates

Games focus on:
- Configuration and entity definition
- Game-specific logic in callbacks
- Resource/asset management
- Game state handling

## Implementation Considerations

### Dynamic Configuration
#### Advantages
- Maximum flexibility
- Easy to modify at runtime
- No compile-time limitations
- Simple to prototype with

#### Disadvantages
- Runtime overhead
- Memory fragmentation possible
- No compile-time optimizations
- Additional pointer indirection

### Static Configuration
#### Advantages
- Optimal performance
- No runtime overhead
- Better cache utilization
- Type-safe interfaces
- Compile-time error checking

#### Disadvantages
- More complex implementation
- Requires rebuild for configuration changes
- Advanced C knowledge required
- More sophisticated build system needed

### Memory Management Considerations
- Prefer explicit size types (uint8_t*) over void* for cross-platform consistency
- Be aware of pointer size differences between 32-bit and 64-bit systems
- Use uintptr_t when you need to do pointer arithmetic
- Consider whether single-block allocation fits your use case
- Think about alignment requirements when calculating offsets
- Plan your memory cleanup strategy
- Document memory ownership clearly

## Future Development

### Planned Systems
- Advanced AI systems
- Multiple physics types
- Various rendering backends
- Network gameplay options
- Asset streaming systems
- Scripting integration
- Terrain generation
- Particle systems
- Audio subsystems

### Migration Path
1. Start with dynamic configuration
2. Keep systems modular and independent
3. Design clean interfaces
4. Plan for static configuration
5. Gradually introduce compile-time features
6. Maintain backward compatibility

### Immediate Next Steps
1. Decide on memory allocation strategy (single block vs separate)
2. Create clear separation between public and internal headers
3. Implement proper cleanup functions
4. Add error handling for memory operations
5. Consider adding debug logging for memory operations
