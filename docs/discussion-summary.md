# Game Engine Development Discussion Summary

## Project Context
- Building a game engine called "Mandarax" (named after the computer from Vonnegut's Galápagos)
- Planning to eventually establish Mandarax Studios/Games as a company
- Using LLMs to assist in development and learning process

## Naming Conventions and Structure

### Engine Prefix Style
- Adopted C-style naming convention using short prefixes
- Chosen prefix: `mx_` for Mandarax
- Examples:
  ```c
  mx_window_create()
  mx_renderer_init()
  mx_entity_spawn()
  ```

### Repository Structure
- Simple repository name: `mandarax` (without "-engine" suffix)
- Following successful examples like Godot, Raylib, etc.
- Repository URL structure: `github.com/mandaraxgames/mandarax`

### Project Organization
Settled on a pragmatic flat structure with selective modularity:
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

Key principles:
- Start flat and simple
- Create modules only when needed
- Keep related .c and .h files together
- Allow internal coupling where practical

## Engine and Game Integration

### Repository Setup
Using Git submodules for game projects:
```bash
# Create game repo
mkdir my_game
cd my_game
git init
git submodule add https://github.com/you/mandarax.git
```

### Engine API Design
- Using opaque pointers for clean interface
- Engine provides framework and systems
- Games configure through structured API:

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

// Engine provides:
- Core application lifecycle
- Entity management
- Physics system
- Rendering system
- Fixed/variable timestep updates

// Games focus on:
- Configuration and entity definition
- Game-specific logic in callbacks
- Resource/asset management
- Game state handling
```

## Current Development Approach
- Creating separate engine repository immediately
- Building engine features based on game needs
- Using Git submodules to integrate engine into game projects
- Following Godot-like pattern where engine provides framework and games provide configuration

## Next Steps
The discussion concluded with focus on engine API design, specifically:
- Configuration-based game setup
- Lifecycle hooks for game logic
- Entity-component style systems
- Clear separation between engine systems and game logic
