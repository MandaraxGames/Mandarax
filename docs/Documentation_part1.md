# Mandarax Game Engine Documentation

## Project Overview
- Building a game engine called "Mandarax" (named after the computer from Vonnegut's Galápagos)
- Planning to eventually establish Mandarax Studios/Games as a company
- Using LLMs to assist in development and learning process
- Focus on cross-platform development in C
- Interest in memory-efficient design patterns
- Currently at version 0.0.0.1 (experimental/volatile API)

## Engine Architecture

### Core Design Philosophy
- Start flat and simple
- Create modules only when needed
- Keep related .c and .h files together
- Allow internal coupling where practical
- Focus on data-oriented design principles
- Prioritize runtime performance over API stability during early development

### Current Development Focus
#### Entity and Sprite System
- Flat entity structure with component slots
- Data-oriented component storage
- Efficient memory layout and cache utilization
- Flexible component attachment/detachment

#### Implementation Timeline
1. Entity Management (2-3 days)
   - Handle-based entity system
   - Component slot allocation
   - Entity lifecycle management
   
2. Basic Components (2-3 days)
   - Position2D component
   - Sprite component
   - Component data storage

3. Rendering System (2-3 days)
   - Sprite batch rendering
   - Transform handling
   - Basic camera support

4. Movement System (2-3 days)
   - Velocity component
   - Input processing
   - Basic collision detection

5. Integration (2-3 days)
   - Entity factories
   - Resource management
   - Basic scene handling

### Repository Structure
```
mandarax/
  src/
    # Core files stay flat
    mx_types.h       # Basic types
    mx_core.c/h      # Core functionality
    mx_memory.c/h    # Memory management
    mx_renderer.c/h  # Rendering system
    
    # Entity system files
    mx_entity.c/h    # Entity management
    mx_component.c/h # Component system
    mx_sprite.c/h    # Sprite rendering
    mx_transform.c/h # Transform handling
    
    # Optional systems
    mx_physics.c/h   # Physics system
    mx_input.c/h     # Input handling
    mx_scene.c/h     # Scene management
```

### Naming Conventions
- Prefix: `mx_` for all Mandarax identifiers
- Handle types: `MX_EntityHandle`, `MX_ComponentHandle`
- Internal types: `MX_Entity`, `MX_Component`
- Functions: `mx_entity_create()`, `mx_component_attach()`

## Technical Implementation

### Entity System Design

#### Core Entity Structure
```c
typedef struct {
    uint64_t id;                    // Unique identifier
    uint32_t active_components;     // Bitfield of active slots
    void* components[MAX_COMPONENTS]; // Component pointers
    uint32_t flags;                 // Entity state flags
} MX_Entity;
```

#### Component System
```c
// Base component header (shared by all components)
typedef struct {
    uint32_t type;      // Component type identifier
    uint32_t flags;     // Component state flags
    uint64_t entity_id; // Owner entity ID
} MX_ComponentHeader;

// Example components
typedef struct {
    MX_ComponentHeader header;
    float x, y;
    float rotation;
    float scale_x, scale_y;
} MX_Transform2D;

typedef struct {
    MX_ComponentHeader header;
    SDL_Texture* texture;
    SDL_Rect src_rect;  // Source rectangle for sprites
    int width, height;
    uint32_t flags;     // Rendering flags
} MX_Sprite;
```

### Memory Management

#### Component Pool System
```c
typedef struct {
    void* data;              // Raw memory block
    uint32_t chunk_size;     // Size of each element
    uint32_t capacity;       // Maximum elements
    uint32_t count;          // Current element count
    uint32_t* free_list;     // Indices of free slots
    uint32_t free_count;     // Number of free slots
} MX_ComponentPool;
```

#### Memory Layout Considerations
- Components grouped by type for cache efficiency
- Minimal pointer indirection
- Aligned memory access
- Pool-based allocation for stable memory usage

### Data-Oriented Design Principles

#### Component Data Layout
- Store component data in contiguous arrays
- Group frequently accessed data together
- Minimize cache misses during system updates
- Enable SIMD operations where possible

#### System Processing
- Batch process similar components
- Minimize branching in hot paths
- Keep data transformation local
- Enable parallel processing where beneficial

[Continued in Part 2...]
