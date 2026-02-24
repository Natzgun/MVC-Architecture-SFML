#pragma once

#include "Engine/Graphics/Renderer.hpp"
#include "Engine/Input/InputManager.hpp"
#include "Engine/Audio/AudioManager.hpp"
#include "Engine/Scene/SceneManager.hpp"
#include "Engine/Event/EventBus.hpp"
#include "Engine/Assets/AssetManager.hpp"
#include <string>
#include <memory>

namespace Engine {

/// Shared context providing access to all engine subsystems.
///
/// Scenes and game code receive a reference to this struct, giving
/// them access to rendering, input, audio, scene management,
/// events, and asset caches without depending on the Application
/// class directly.
///
/// This is the single "service locator" that replaces the old
/// GameData struct, but with proper module separation.
struct Context {
    Renderer&       renderer;
    InputManager&   input;
    AudioManager&   audio;
    SceneManager&   scenes;
    EventBus&       events;
    TextureManager  textures;
    FontManager     fonts;
    SoundBufferManager sounds;
};

/// Core engine class that owns all subsystems and runs the game loop.
///
/// Application creates and wires together all modules (Renderer,
/// InputManager, AudioManager, SceneManager, EventBus, AssetManagers),
/// exposes them through a Context struct, and drives the fixed-timestep
/// game loop.
///
/// Usage:
/// @code
///   Engine::Application app(1280, 720, "My Game");
///   app.context().scenes.pushScene(
///       std::make_unique<MyScene>(app.context()));
///   app.run();
/// @endcode
class Application {
public:
    /// Construct the application with a window of the given size and title.
    /// @param width  Window width in pixels.
    /// @param height Window height in pixels.
    /// @param title  Window title.
    Application(unsigned int width, unsigned int height, const std::string& title);
    ~Application() = default;

    // Non-copyable, non-movable
    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;
    Application(Application&&) = delete;
    Application& operator=(Application&&) = delete;

    /// Start the main game loop. Blocks until the window is closed
    /// or the scene stack becomes empty.
    void run();

    /// Get the shared context (all engine subsystems).
    [[nodiscard]] Context& context();
    [[nodiscard]] const Context& context() const;

private:
    static constexpr float dt = 1.0f / 60.0f; ///< Fixed timestep (60 Hz)
    sf::Clock m_clock;

    // Owned subsystems
    Renderer     m_renderer;
    InputManager m_input;
    AudioManager m_audio;
    SceneManager m_scenes;
    EventBus     m_events;

    // Context binds references to owned subsystems
    Context m_context;
};

} // namespace Engine
