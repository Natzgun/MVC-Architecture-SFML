#pragma once

namespace Engine {

/// Abstract base class for all game scenes.
///
/// Each scene represents a distinct screen or phase of the game
/// (e.g., MainMenu, Gameplay, Pause, GameOver).
///
/// Lifecycle: init() -> [handleInput() -> update() -> draw()]* -> ~Scene()
///
/// Scenes are managed by the SceneManager via a stack, enabling
/// push/pop transitions (e.g., pausing overlays).
///
/// Scenes receive engine subsystems through a Context struct rather than
/// storing raw pointers, promoting loose coupling. The Application class
/// orchestrates the calls and provides the correct references.
class Scene {
public:
    virtual ~Scene() = default;

    /// Called once when the scene is first pushed onto the stack.
    /// Use this to load resources, bind input actions, and create entities.
    virtual void init() = 0;

    /// Process input each frame. The InputManager has already polled
    /// events before this is called.
    /// @param dt Delta time (useful for input-related timing).
    virtual void handleInput(float dt) = 0;

    /// Update game logic at a fixed timestep.
    /// @param dt Fixed delta time in seconds (e.g., 1/60).
    virtual void update(float dt) = 0;

    /// Render the current frame.
    /// @param interpolation Value in [0,1] for smoothing between physics steps.
    virtual void draw(float interpolation) = 0;

    /// Called when another scene is pushed on top of this one.
    virtual void pause() {}

    /// Called when the scene above this one is popped.
    virtual void resume() {}
};

} // namespace Engine
