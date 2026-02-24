# SFML 3 Game Template

A scalable, ready-to-use C++17 game engine template built on **SFML 3.0**. Clone this repository and start building your own 2D game immediately.

## Features

- **Fixed-timestep game loop** with interpolation for smooth rendering.
- **Stack-based state machine** for scene management (menus, gameplay, pause, etc.).
- **Generic resource manager** (textures, fonts, sounds) with caching.
- **SFML 3.0 API** -- uses the modern event system (`std::optional`, `pollEvent`, scoped enums).
- **SOLID principles** -- small interfaces, dependency inversion, single responsibility per class.
- **CMake + FetchContent** -- no manual SFML installation required.

## Project Structure

```
.
├── include/                    # Headers (.hpp)
│   ├── Core/
│   │   ├── Game.hpp            # Engine core: window, game loop, shared context
│   │   └── ResourceManager.hpp # Template-based asset cache
│   ├── States/
│   │   ├── State.hpp           # Abstract base class for all states
│   │   └── StateMachine.hpp    # Stack-based state manager
│   └── Example/
│       └── DemoState.hpp       # Example state (replace with your own)
├── src/                        # Implementations (.cpp)
│   ├── Core/
│   │   └── Game.cpp
│   ├── States/
│   │   └── StateMachine.cpp
│   ├── Example/
│   │   └── DemoState.cpp       # Example state (replace with your own)
│   └── main.cpp                # Entry point
├── assets/                     # Game assets (images, audio, fonts)
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

### 1. Create Your First State

A **State** is a self-contained game scene (menu, level, game over, etc.). Create a new class that inherits from `Engine::State`:

```cpp
// include/MyGame/PlayState.hpp
#pragma once
#include "States/State.hpp"
#include "Core/Game.hpp"

class PlayState : public Engine::State {
public:
    explicit PlayState(Engine::GameDataRef data) : m_data(std::move(data)) {}

    void init() override {
        // Load resources, create entities
    }

    void handleInput() override {
        while (const auto event = m_data->window->pollEvent()) {
            if (event->is<sf::Event::Closed>())
                m_data->window->close();
        }
    }

    void update(float dt) override {
        // Game logic here
    }

    void draw(float interpolation) override {
        // Render here
        m_data->window->draw(mySprite);
    }

private:
    Engine::GameDataRef m_data;
};
```

### 2. Register It in main.cpp

```cpp
#include "Core/Game.hpp"
#include "MyGame/PlayState.hpp"

int main() {
    Engine::Game game(1280, 720, "My Game");
    game.getContext()->machine->pushState(
        std::make_unique<PlayState>(game.getContext()));
    game.run();
}
```

### 3. Switch Between States

From inside any state you can push, replace, or pop states:

```cpp
// Push a new state on top (current state is paused)
m_data->machine->pushState(std::make_unique<PauseState>(m_data), false);

// Replace the current state entirely
m_data->machine->pushState(std::make_unique<GameOverState>(m_data), true);

// Pop the current state (resumes the one below)
m_data->machine->popState();
```

### 4. Load Resources

Use the built-in resource managers available through `GameData`:

```cpp
// In your state's init()
m_data->textures.load("player", "assets/player.png");
m_data->fonts.load("main", "assets/font.ttf");
m_data->sounds.load("jump", "assets/jump.wav");

// Later, retrieve them
sf::Sprite player(m_data->textures.get("player"));
```

## Architecture Overview

```
main.cpp
  └── Engine::Game
        ├── sf::RenderWindow       (SFML 3 window)
        ├── StateMachine           (stack of States)
        │     ├── State A          (e.g., MainMenu)
        │     ├── State B          (e.g., Gameplay)
        │     └── ...
        └── Resource Managers
              ├── TextureManager
              ├── FontManager
              └── SoundBufferManager
```

**Game loop** (each frame):
1. `processStateChanges()` -- apply pending push/pop.
2. `handleInput()` -- poll SFML events + real-time input.
3. `update(dt)` -- fixed-timestep logic (may run multiple times per frame).
4. `draw(interpolation)` -- render with smoothing factor.

## Design Principles

| Principle | Application |
|-----------|-------------|
| **Single Responsibility** | Each class has one job: `Game` runs the loop, `StateMachine` manages transitions, `State` owns scene logic. |
| **Open/Closed** | Add new states without modifying engine code. |
| **Liskov Substitution** | Any `State` subclass works seamlessly in the `StateMachine`. |
| **Interface Segregation** | `State` exposes only the methods the engine needs. |
| **Dependency Inversion** | States depend on the abstract `State` interface, not concrete implementations. The engine is decoupled from game logic. |

## License

This project is licensed under the **Apache License 2.0**. See the [LICENSE](LICENSE) file for details.
