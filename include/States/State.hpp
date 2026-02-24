#pragma once

namespace Engine {

/// Abstract base class for all game states (scenes).
/// Each state represents a distinct screen or phase of the game
/// (e.g., MainMenu, Gameplay, Pause, GameOver).
///
/// Lifecycle: init() -> [handleInput() -> update() -> draw()]* -> ~State()
///
/// States are managed by the StateMachine via a stack, enabling
/// push/pop transitions (e.g., pausing overlays).
class State {
public:
    virtual ~State() = default;

    /// Called once when the state is first pushed onto the stack.
    /// Use this to load resources and initialize entities.
    virtual void init() = 0;

    /// Process window events and real-time input each frame.
    virtual void handleInput() = 0;

    /// Update game logic at a fixed timestep.
    /// @param dt Fixed delta time in seconds (e.g., 1/60).
    virtual void update(float dt) = 0;

    /// Render the current frame.
    /// @param interpolation Value in [0,1] for smoothing between physics steps.
    virtual void draw(float interpolation) = 0;

    /// Called when another state is pushed on top of this one.
    virtual void pause() {}

    /// Called when the state above this one is popped.
    virtual void resume() {}
};

} // namespace Engine
