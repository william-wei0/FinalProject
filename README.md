# 2D Tile-Based C++ Game Engine

A 2D top-down action game engine built with C++ and OpenGL, inspired by *The Legend of Zelda* built for CS-3113 Introduction to Game Design. Features a scene-based architecture, tile map rendering, entity collision, enemy AI, and audio support.

---

## Dependencies

- **SDL2** — windowing, input, and audio context
- **SDL2_mixer** — background music and sound effects
- **OpenGL / GLEW** — rendering
- **GLM** — math (vectors, matrices, transforms)
- **STB Image** — texture loading

---

## Project Structure

```
project/
├── main.cpp                  # Entry point, game loop, scene switching
├── Scene.h                   # Abstract base class for all scenes
├── Entity.h / Entity.cpp     # Player, enemies, weapons, projectiles
├── Map.h / Map.cpp           # Tile map building and collision
├── Effects.h / Effects.cpp   # Visual effects (fade, shake, grow/shrink)
├── Utility.h / Utility.cpp   # Texture loading, text rendering helpers
├── ShaderProgram.h/.cpp      # OpenGL shader wrapper
├── shaders/
│   ├── vertex_lit.glsl
│   ├── fragment_lit.glsl
│   ├── vertex_textured.glsl
│   └── fragment_textured.glsl
├── levels/
│   ├── MainMenu.h / MainMenu.cpp
│   ├── LevelA.h / LevelA.cpp
│   ├── LevelB.h / LevelB.cpp
│   └── LevelC.h / LevelC.cpp
└── assets/
    ├── minish_cap_tileset.png
    ├── LinkU.png
    ├── sword.png
    ├── octorock.png
    ├── armos.png
    ├── sphere.png
    ├── font1.png
    ├── sword.wav
    ├── death.wav
```

---

## Core Systems

### Scene System (`Scene.h`)
All levels inherit from the abstract `Scene` class and implement four methods:

```cpp
virtual void initialise()                      = 0;
virtual void update(float delta_time)          = 0;
virtual void render(ShaderProgram *program)    = 0;
virtual void move_camera(glm::mat4 &view)      = 0;
```

Each scene owns a `GameState` struct containing pointers to the map, player, enemies, weapon, and audio handles. Scene transitions are handled by setting `next_scene_id` — the main loop picks this up and calls `switch_to_scene()`.

### Entity System (`Entity.h/.cpp`)
A single `Entity` class covers players, enemies, weapons, and projectiles, distinguished by `EntityType`. Key features include:

- **Sprite animation** from a texture atlas
- **AABB collision** against other entities and tile maps
- **Facing direction** tracking for directional sword hits
- **AI behaviors**: `GUARD`, `WALKER`, `SHOOTER`, `PROJECTILE`

### Map System (`Map.h/.cpp`)
Maps are defined as flat `unsigned int` arrays of tile indices into a spritesheet. The `Map::build()` method constructs vertex and UV buffers at load time for efficient rendering. `Map::is_solid()` performs point-based tile collision queries used by entities each frame.

Tiles listed in the `switch` statement inside `is_solid()` are treated as passable (e.g. decorative tiles, open ground).

### Effects System (`Effects.h/.cpp`)
Supports the following screen effects:

| Effect   | Description                        |
|----------|------------------------------------|
| `FADEIN` | Black overlay fades out            |
| `FADEOUT`| Black overlay fades in             |
| `GROW`   | Overlay expands from center        |
| `SHRINK` | Overlay contracts to nothing       |
| `SHAKE`  | Camera jitter via view translation |

---

## Controls

| Key         | Action              |
|-------------|---------------------|
| Arrow Keys  | Move player         |
| Left Shift  | Swing sword         |
| Enter       | Confirm / menu select |
| `1` / `2` / `3` | Jump to scene (debug) |
| `Q`         | Quit                |

---

## Adding a New Level

1. Create `LevelX.h` and `LevelX.cpp` in the `levels/` folder.
2. Inherit from `Scene` and implement all four virtual methods.
3. Define a `LEVEL_DATA` array of tile indices matching your tileset layout.
4. Register the level in `main.cpp`:

```cpp
#include "levels/LevelX.h"

LevelX *g_level_x = new LevelX();
g_levels[4] = g_level_x;   // extend the array as needed
```

5. Trigger the transition from any scene by setting:

```cpp
m_game_state.next_scene_id = 4;
```

---

## Building

This project uses standard OpenGL/SDL2 build tooling. Link against:

```
-lSDL2 -lSDL2_mixer -lGLEW -lGL -lGLU
```

On Windows, ensure GLEW is initialized before any GL calls (`glewInit()` is called in `initialise()` under `#ifdef _WINDOWS`).

---

## Notes

- Lives persist across scene transitions via `set_lives()` / `get_lives()` on the `Scene` base class.
- The camera uses an orthographic projection scaled by `CAMERA_SCALE` (default `1.3`) and follows the player with clamped bounds defined per level.
- A fixed timestep of `~60 FPS` (`0.0166666s`) is used for deterministic physics updates.
