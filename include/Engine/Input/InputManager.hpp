#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <functional>
#include <unordered_map>
#include <vector>

namespace Engine {

// Forward declaration
class Renderer;

/// Action identifiers for input bindings.
/// Users define string-based action names and bind them to keys.
using Action = std::string;

/// Abstraction layer for keyboard, mouse, and joystick input.
///
/// Provides two input models:
/// 1. **Event-based**: SFML window events (key press/release, mouse clicks).
///    Processed via pollEvents() which must be called once per frame.
/// 2. **Real-time**: Instantaneous key/button state queries for smooth movement.
///
/// Supports action mapping: bind logical action names to physical keys,
/// then query actions instead of raw keys. This allows rebinding without
/// changing game logic.
///
/// Usage:
/// @code
///   inputManager.bindKey("move_up", sf::Keyboard::Key::W);
///   inputManager.bindKey("move_up", sf::Keyboard::Key::Up);
///   // Later in update:
///   if (inputManager.isActionHeld("move_up")) { ... }
/// @endcode
class InputManager {
public:
    /// Callback type for key press/release events.
    using KeyCallback = std::function<void()>;

    InputManager() = default;
    ~InputManager() = default;

    // Non-copyable, movable
    InputManager(const InputManager&) = delete;
    InputManager& operator=(const InputManager&) = delete;
    InputManager(InputManager&&) = default;
    InputManager& operator=(InputManager&&) = default;

    /// Poll all pending SFML window events.
    /// Must be called once per frame before any input queries.
    /// Handles window close events internally by closing the window.
    /// @param renderer The renderer that owns the window to poll events from.
    void pollEvents(Renderer& renderer);

    // ---- Action mapping ----

    /// Bind a keyboard key to a named action.
    /// Multiple keys can be bound to the same action.
    void bindKey(const Action& action, sf::Keyboard::Key key);

    /// Remove all key bindings for a given action.
    void unbindAction(const Action& action);

    /// Remove all key bindings.
    void clearBindings();

    // ---- Real-time queries ----

    /// Check if any key bound to the action is currently held down.
    [[nodiscard]] bool isActionHeld(const Action& action) const;

    /// Check if a specific keyboard key is currently held down.
    [[nodiscard]] static bool isKeyHeld(sf::Keyboard::Key key);

    /// Check if a mouse button is currently held down.
    [[nodiscard]] static bool isMouseButtonHeld(sf::Mouse::Button button);

    /// Get the current mouse position relative to the window.
    [[nodiscard]] sf::Vector2i getMousePosition(const Renderer& renderer) const;

    // ---- Event-based queries (per-frame, reset each pollEvents call) ----

    /// Check if a key bound to the action was pressed this frame.
    [[nodiscard]] bool isActionPressed(const Action& action) const;

    /// Check if a key bound to the action was released this frame.
    [[nodiscard]] bool isActionReleased(const Action& action) const;

    /// Check if the window close was requested this frame.
    [[nodiscard]] bool isWindowCloseRequested() const;

private:
    /// Keys bound to each action.
    std::unordered_map<Action, std::vector<sf::Keyboard::Key>> m_bindings;

    /// Keys that were pressed this frame.
    std::vector<sf::Keyboard::Key> m_pressedThisFrame;

    /// Keys that were released this frame.
    std::vector<sf::Keyboard::Key> m_releasedThisFrame;

    /// Whether window close was requested this frame.
    bool m_closeRequested = false;
};

} // namespace Engine
