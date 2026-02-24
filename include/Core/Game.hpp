#pragma once

#include <SFML/Graphics.hpp>
#include "States/StateMachine.hpp"
#include "Core/ResourceManager.hpp"
#include <memory>
#include <string>

namespace Engine {

/// Shared context that holds all engine subsystems.
/// Every State receives a shared_ptr to this struct, giving it
/// access to the window, state machine, and resource managers.
struct GameData {
    std::unique_ptr<StateMachine> machine;
    std::unique_ptr<sf::RenderWindow> window;
    TextureManager textures;
    FontManager fonts;
    SoundBufferManager sounds;
};

using GameDataRef = std::shared_ptr<GameData>;

/// Core engine class. Creates the window, initializes subsystems,
/// and runs the main game loop with a fixed-timestep update.
///
/// Usage:
/// @code
///   Engine::Game game(1280, 720, "My Game");
///   game.getContext()->machine->pushState(std::make_unique<MyState>(game.getContext()));
///   game.run();
/// @endcode
class Game {
public:
    /// Construct the engine with a window of the given size and title.
    /// @param width  Window width in pixels.
    /// @param height Window height in pixels.
    /// @param title  Window title.
    Game(unsigned int width, unsigned int height, const std::string& title);
    ~Game() = default;

    /// Start the main game loop. Blocks until the window is closed
    /// or the state stack becomes empty.
    void run();

    /// Get the shared context (window, state machine, resource managers).
    [[nodiscard]] GameDataRef getContext() const { return m_data; }

private:
    static constexpr float dt = 1.0f / 60.0f; // Fixed timestep (60 Hz)
    sf::Clock m_clock;
    GameDataRef m_data = std::make_shared<GameData>();
};

} // namespace Engine
