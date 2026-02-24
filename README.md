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
│   ├── Engine/
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
│   └── Example/
│       └── DemoScene.hpp           # Example scene (replace with your own)
├── src/
│   ├── Engine/
│   │   ├── Core/Application.cpp
│   │   ├── Graphics/Renderer.cpp
│   │   ├── Input/InputManager.cpp
│   │   ├── Audio/AudioManager.cpp
│   │   └── Scene/SceneManager.cpp
│   ├── Example/
│   │   └── DemoScene.cpp           # Example scene (replace with your own)
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
