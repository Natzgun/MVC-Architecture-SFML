# SFML 3 Modular Game Engine Template

A scalable, modular C++17 game engine template built on **SFML 3.0**. Clone this repository and start building your own 2D game immediately.

## Features

- **Modular architecture** -- self-contained modules (Input, Graphics, Audio, Scene, Event, Assets) with clear boundaries.
- **Fixed-timestep game loop** with interpolation for smooth rendering.
- **Stack-based scene manager** for scene transitions (menus, gameplay, pause, etc.).
- **Action-mapped input system** -- bind logical actions to physical keys; rebind without changing game logic.
- **Type-erased EventBus** -- Observer pattern for decoupled inter-module communication.
- **Audio manager** -- pooled sound effects and streaming music playback.
- **Generic asset manager** (textures, fonts, sounds) with caching.
- **SFML 3.0 API** -- uses the modern event system (`std::optional`, `pollEvent`, scoped enums).
- **SOLID principles** -- single responsibility per module, dependency inversion via Context.
- **CMake + FetchContent** -- no manual SFML installation required.

## Project Structure

```
.
├── include/
│   ├── Engine/                     # Engine modules (DO NOT MODIFY)
│   │   ├── Core/
│   │   │   └── Application.hpp     # Entry point, game loop, Context struct
│   │   ├── Input/
│   │   │   └── InputManager.hpp    # Action-mapped keyboard/mouse abstraction
│   │   ├── Graphics/
│   │   │   └── Renderer.hpp        # Rendering abstraction over sf::RenderWindow
│   │   ├── Audio/
│   │   │   └── AudioManager.hpp    # Sound effects + music streaming
│   │   ├── Scene/
│   │   │   ├── Scene.hpp           # Abstract base class for all scenes
│   │   │   └── SceneManager.hpp    # Stack-based scene management
│   │   ├── Event/
│   │   │   └── EventBus.hpp        # Type-erased publish/subscribe system
│   │   └── Assets/
│   │       └── AssetManager.hpp    # Template-based resource cache
│   └── Example/                    # Reference code (copy, rename, make it yours)
│       ├── DemoScene.hpp           # Movable circle demo scene
│       ├── Entities/
│       │   └── Entity.hpp          # Base class: position, velocity, bounds
│       ├── Physics/
│       │   └── Collision.hpp       # AABB collision detection & resolution
│       ├── Animation/
│       │   └── SpriteAnimator.hpp  # Frame-based sprite sheet animation
│       ├── Camera/
│       │   └── Camera.hpp          # 2D camera with smooth follow & bounds
│       ├── UI/
│       │   └── HUD.hpp             # Base class for screen-space UI overlays
│       └── Scenes/
│           ├── MenuScene.hpp       # Title screen (Start / Exit)
│           └── PauseScene.hpp      # Pause overlay (Resume / Quit)
├── src/
│   ├── Engine/
│   │   ├── Core/Application.cpp
│   │   ├── Graphics/Renderer.cpp
│   │   ├── Input/InputManager.cpp
│   │   ├── Audio/AudioManager.cpp
│   │   └── Scene/SceneManager.cpp
│   ├── Example/
│   │   ├── DemoScene.cpp
│   │   ├── Entities/Entity.cpp
│   │   ├── Physics/Collision.cpp
│   │   ├── Animation/SpriteAnimator.cpp
│   │   ├── Camera/Camera.cpp
│   │   ├── UI/HUD.cpp
│   │   └── Scenes/
│   │       ├── MenuScene.cpp
│   │       └── PauseScene.cpp
│   └── main.cpp                    # Entry point
├── assets/                         # Game assets (images, audio, fonts)
├── CMakeLists.txt
├── LICENSE
└── README.md
```

## Quick Start

### Prerequisites

- C++17 compiler (GCC 9+, Clang 9+, MSVC 2019+)
- CMake 3.28+
- On Linux, install SFML system dependencies:
  ```bash
  # Debian / Ubuntu
  sudo apt update && sudo apt install \
      libxrandr-dev libxcursor-dev libxi-dev libudev-dev \
      libfreetype-dev libflac-dev libvorbis-dev \
      libgl1-mesa-dev libegl1-mesa-dev
  ```
- Fedora (Tested in 43)
  ```bash
  sudo dnf install \
          libXrandr-devel \
          libXcursor-devel \
          libXi-devel \
          systemd-devel \
          freetype-devel \
          flac-devel \
          libvorbis-devel \
          mesa-libGL-devel \
          mesa-libEGL-devel
  ```
  

### Build & Run

```bash
cmake -B build
cmake --build build
./build/bin/SFMLGameTemplate
```

## How to Use This Template

### 1. Create Your First Scene

A **Scene** is a self-contained game screen (menu, level, game over, etc.). Create a new class that inherits from `Engine::Scene`:

```cpp
// include/MyGame/PlayScene.hpp
#pragma once
#include "Engine/Scene/Scene.hpp"
#include "Engine/Core/Application.hpp"

class PlayScene : public Engine::Scene {
public:
    explicit PlayScene(Engine::Context& ctx) : m_ctx(ctx) {}

    void init() override {
        // Bind input actions
        m_ctx.input.bindKey("jump", sf::Keyboard::Key::Space);

        // Load resources
        m_ctx.textures.load("player", "assets/player.png");
    }

    void handleInput(float dt) override {
        if (m_ctx.input.isActionPressed("jump")) {
            // Handle jump
        }
    }

    void update(float dt) override {
        // Game logic here
    }

    void draw(float interpolation) override {
        m_ctx.renderer.draw(mySprite);
    }

private:
    Engine::Context& m_ctx;
};
```

### 2. Register It in main.cpp

```cpp
#include "Engine/Core/Application.hpp"
#include "MyGame/PlayScene.hpp"

int main() {
    Engine::Application app(1280, 720, "My Game");
    app.context().scenes.pushScene(
        std::make_unique<PlayScene>(app.context()));
    app.run();
}
```

### 3. Switch Between Scenes

From inside any scene you can push, replace, or pop scenes:

```cpp
// Push a new scene on top (current scene is paused)
m_ctx.scenes.pushScene(std::make_unique<PauseScene>(m_ctx), false);

// Replace the current scene entirely
m_ctx.scenes.pushScene(std::make_unique<GameOverScene>(m_ctx), true);

// Pop the current scene (resumes the one below)
m_ctx.scenes.popScene();
```

### 4. Use the Input System

Bind logical action names to physical keys. Query actions instead of raw keys:

```cpp
void init() override {
    m_ctx.input.bindKey("move_up",    sf::Keyboard::Key::W);
    m_ctx.input.bindKey("move_up",    sf::Keyboard::Key::Up);   // multiple keys per action
    m_ctx.input.bindKey("shoot",      sf::Keyboard::Key::Space);
}

void handleInput(float dt) override {
    if (m_ctx.input.isActionHeld("move_up"))    { /* smooth movement */ }
    if (m_ctx.input.isActionPressed("shoot"))   { /* one-shot action */ }
}
```

### 5. Use the EventBus

Publish and subscribe to custom events for decoupled communication:

```cpp
// Define your event
struct EnemyKilled { int score; std::string enemyType; };

// Subscribe (e.g., in a UI scene)
auto id = m_ctx.events.subscribe<EnemyKilled>([this](const EnemyKilled& e) {
    m_score += e.score;
});

// Publish (e.g., in gameplay logic)
m_ctx.events.publish(EnemyKilled{100, "goblin"});

// Unsubscribe when done
m_ctx.events.unsubscribe<EnemyKilled>(id);
```

### 6. Play Audio

```cpp
// Sound effects (load buffer via AssetManager, play via AudioManager)
m_ctx.sounds.load("jump", "assets/audio/jump.wav");
m_ctx.audio.playSound(m_ctx.sounds.get("jump"));

// Streaming music
m_ctx.audio.playMusic("assets/audio/theme.ogg");
m_ctx.audio.setMusicVolume(50.f);
```

### 7. Load Resources

Use the built-in asset managers available through `Context`:

```cpp
m_ctx.textures.load("player", "assets/player.png");
m_ctx.fonts.load("main", "assets/font.ttf");
m_ctx.sounds.load("jump", "assets/jump.wav");

// Retrieve them later
sf::Sprite player(m_ctx.textures.get("player"));
```

## Project Organization by Game Type

The template is intentionally minimal -- how you organize your game code depends on what you're building. Below are recommended structures for common game genres, all using simple inheritance (`Entity` base class with `update`/`draw`).

### Platformer (e.g., Mario, Celeste)

```
include/Game/
├── Scenes/
│   ├── MenuScene.hpp
│   ├── PlayScene.hpp
│   └── GameOverScene.hpp
├── Entities/
│   ├── Entity.hpp            # Base class: position, velocity, update(), draw()
│   ├── Player.hpp
│   ├── Enemy.hpp
│   └── Collectible.hpp
├── Level/
│   ├── Tilemap.hpp           # Load and render tile-based levels
│   └── Camera.hpp            # Follow the player, clamp to level bounds
└── Physics/
    └── Collision.hpp         # AABB or tilemap collision detection
```

**Key decisions:**
- One scene per level or one `PlayScene` that loads different level files.
- A `Tilemap` class that reads a format like CSV or Tiled JSON.
- Simple AABB collision -- no need for a physics engine in most platformers.
- Camera that follows the player with optional smoothing.

### Top-down RPG (e.g., Zelda, Stardew Valley)

```
include/Game/
├── Scenes/
│   ├── TitleScene.hpp
│   ├── WorldScene.hpp
│   ├── BattleScene.hpp       # If using separate battle screen
│   └── DialogScene.hpp       # Push on top of WorldScene
├── Entities/
│   ├── Entity.hpp
│   ├── Player.hpp
│   ├── NPC.hpp
│   └── Item.hpp
├── World/
│   ├── Tilemap.hpp
│   ├── Camera.hpp
│   └── MapLoader.hpp         # Load rooms/zones from files
├── UI/
│   ├── HUD.hpp               # Health bar, inventory display
│   └── DialogBox.hpp
└── Data/
    └── GameData.hpp          # Stats, inventory, quest flags (serializable)
```

**Key decisions:**
- `DialogScene` pushes on top of `WorldScene` (the scene stack handles pausing the world).
- `GameData` holds all persistent state (player stats, inventory, quest progress) and is referenced by scenes via Context or passed explicitly.
- NPCs use simple state logic (patrol, idle, talk) -- no need for complex AI.

### Shoot 'em up / Bullet hell (e.g., Touhou, Ikaruga)

```
include/Game/
├── Scenes/
│   ├── MenuScene.hpp
│   ├── StageScene.hpp
│   └── ResultScene.hpp
├── Entities/
│   ├── Entity.hpp
│   ├── Player.hpp
│   ├── Enemy.hpp
│   └── Bullet.hpp
├── Spawners/
│   ├── WaveManager.hpp       # Spawn enemy waves on a timeline
│   └── BulletPattern.hpp     # Define patterns (spiral, spread, aimed)
└── Systems/
    └── CollisionGrid.hpp     # Spatial partitioning for many bullet-vs-entity checks
```

**Key decisions:**
- Entity pooling is important -- hundreds of bullets per frame. Use `std::vector<Bullet>` with active/inactive flags instead of allocating/deallocating.
- A spatial grid or simple brute-force with early-out can handle collision if entity counts stay under ~1000.
- `WaveManager` reads a timeline (time → spawn function) to script each stage.

### Puzzle game (e.g., Tetris, Match-3, Sokoban)

```
include/Game/
├── Scenes/
│   ├── MenuScene.hpp
│   ├── PuzzleScene.hpp
│   └── ResultScene.hpp
├── Board/
│   ├── Board.hpp             # Grid state, rules, win/lose detection
│   ├── Piece.hpp             # Individual piece or cell
│   └── BoardRenderer.hpp     # Draw the board state
└── UI/
    ├── ScoreDisplay.hpp
    └── Timer.hpp
```

**Key decisions:**
- The game logic lives in `Board`, completely separate from rendering. This makes it testable and clean.
- `BoardRenderer` reads the board state and draws it -- the board itself knows nothing about SFML.
- Input is simple (arrow keys, click) so direct key bindings in `PuzzleScene::handleInput` are enough.

### Fighting game (e.g., Street Fighter, Smash Bros)

```
include/Game/
├── Scenes/
│   ├── CharacterSelectScene.hpp
│   ├── FightScene.hpp
│   └── ResultScene.hpp
├── Entities/
│   ├── Fighter.hpp           # Base: hitboxes, hurtboxes, state machine
│   └── Projectile.hpp
├── Combat/
│   ├── FighterState.hpp      # Idle, Walking, Jumping, Attacking, Hitstun...
│   ├── Hitbox.hpp
│   └── ComboSystem.hpp       # Track input sequences for special moves
└── Animation/
    └── SpriteAnimator.hpp    # Frame-based sprite sheet animation
```

**Key decisions:**
- Each fighter has its own **state machine** (not scenes -- these are entity states like Idle, Attack, Hitstun).
- Hitbox/hurtbox system with frame data is central to fighting games.
- `ComboSystem` buffers recent inputs and matches them against move lists.
- Frame-based animation is critical -- use a `SpriteAnimator` that advances frames at fixed intervals.

### General recommendations

| Concern | Recommendation |
|---------|---------------|
| **Entity base class** | Start with a simple `Entity` with `virtual update(float dt)` and `virtual draw(Renderer&)`. Add what you need later. |
| **When to split files** | One class per header/source pair. If a file exceeds ~300 lines, it probably has two responsibilities. |
| **Scene count** | At minimum: one menu scene, one gameplay scene. Add more as needed (pause, settings, game over). |
| **Folder depth** | Two levels max (`Game/Entities/`, `Game/Scenes/`). Deep nesting adds friction with no benefit. |
| **Game state / save data** | Keep it in a plain struct. Scenes read/write to it. Serialize it for save files. |
| **When to consider ECS** | If you have hundreds of entities with mix-and-match behaviors (e.g., sandbox, RTS). For most 2D games, inheritance is simpler and sufficient. |
| **Physics** | For most 2D games, hand-written AABB collision is enough. Only bring in Box2D if you need realistic rigid body physics. |

## Architecture Overview

```
main.cpp
  └── Engine::Application
        ├── Renderer          (wraps sf::RenderWindow)
        ├── InputManager      (action-mapped keyboard/mouse)
        ├── AudioManager      (sound effects + music)
        ├── SceneManager      (stack of Scenes)
        │     ├── Scene A     (e.g., MainMenu)
        │     ├── Scene B     (e.g., Gameplay)
        │     └── ...
        ├── EventBus          (publish/subscribe messaging)
        └── Asset Managers
              ├── TextureManager
              ├── FontManager
              └── SoundBufferManager
```

All subsystems are accessible through the **Context** struct, which is passed to each scene.

**Game loop** (each frame):
1. `processSceneChanges()` -- apply pending push/pop.
2. `pollEvents()` -- InputManager polls SFML events, tracks key press/release.
3. `handleInput(dt)` -- active scene reads input via action queries.
4. `update(dt)` -- fixed-timestep logic (may run multiple times per frame).
5. `draw(interpolation)` -- render with smoothing factor through Renderer.

## Module Responsibilities

| Module | Responsibility |
|--------|---------------|
| **Core/Application** | Owns all subsystems, runs the game loop, provides Context. |
| **Graphics/Renderer** | Wraps sf::RenderWindow; clear, draw, display. Decouples scenes from raw window. |
| **Input/InputManager** | Polls SFML events, tracks per-frame key state, provides action-mapped queries. |
| **Audio/AudioManager** | Pooled sound effect playback, streaming music, volume control. |
| **Scene/SceneManager** | Stack-based scene transitions with deferred processing. |
| **Scene/Scene** | Abstract interface for game screens (init, input, update, draw, pause/resume). |
| **Event/EventBus** | Type-erased Observer pattern for decoupled inter-module communication. |
| **Assets/AssetManager** | Template resource cache for textures, fonts, sound buffers. |

## Design Principles

| Principle | Application |
|-----------|-------------|
| **Single Responsibility** | Each module has one job: Renderer renders, InputManager handles input, etc. |
| **Open/Closed** | Add new scenes and event types without modifying engine code. |
| **Liskov Substitution** | Any Scene subclass works seamlessly in the SceneManager. |
| **Interface Segregation** | Scene exposes only the methods the engine needs. Modules expose minimal APIs. |
| **Dependency Inversion** | Scenes depend on abstract interfaces (Scene base, Context), not concrete implementations. |
| **DRY** | AssetManager is a single template for all resource types. EventBus handles all event types. |
| **KISS** | Each module is small, focused, and easy to understand independently. |

## Design Patterns

| Pattern | Where |
|---------|-------|
| **State Machine** | SceneManager -- stack-based scene transitions |
| **Observer** | EventBus -- publish/subscribe for decoupled events |
| **Command** | InputManager -- action bindings map logical commands to physical keys |
| **Service Locator** | Context struct -- provides access to all engine subsystems |

## License

This project is licensed under the **Apache License 2.0**. See the [LICENSE](LICENSE) file for details.
