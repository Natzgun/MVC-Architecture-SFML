#pragma once

#include <SFML/Graphics.hpp>
#include <string>

namespace Engine {

/// Abstraction layer over sf::RenderWindow for all rendering operations.
///
/// Decouples game code from direct window manipulation. Scenes draw
/// through the Renderer instead of holding a raw pointer to the window.
/// This enables future enhancements like render-to-texture, viewports,
/// or batching without changing scene code.
///
/// The Renderer owns the sf::RenderWindow instance.
class Renderer {
public:
    /// Create a renderer with a window of the given size and title.
    /// @param width  Window width in pixels.
    /// @param height Window height in pixels.
    /// @param title  Window title string.
    Renderer(unsigned int width, unsigned int height, const std::string& title);
    ~Renderer() = default;

    // Non-copyable, non-movable (owns the window)
    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;
    Renderer(Renderer&&) = delete;
    Renderer& operator=(Renderer&&) = delete;

    /// Clear the window with the given color.
    void clear(sf::Color color = sf::Color::Black);

    /// Draw any SFML drawable object.
    void draw(const sf::Drawable& drawable);

    /// Draw a drawable with a render states configuration.
    void draw(const sf::Drawable& drawable, const sf::RenderStates& states);

    /// Present the rendered frame to the screen.
    void display();

    /// Check if the window is currently open.
    [[nodiscard]] bool isOpen() const;

    /// Close the window.
    void close();

    /// Set the framerate limit.
    void setFramerateLimit(unsigned int limit);

    /// Get the window size.
    [[nodiscard]] sf::Vector2u getSize() const;

    /// Set the window view (camera).
    void setView(const sf::View& view);

    /// Get the current window view.
    [[nodiscard]] const sf::View& getView() const;

    /// Get the default window view.
    [[nodiscard]] const sf::View& getDefaultView() const;

    /// Get direct access to the underlying sf::RenderWindow.
    /// Prefer using Renderer methods, but this is available for
    /// advanced use cases (e.g., polling events in InputManager).
    [[nodiscard]] sf::RenderWindow& getWindow();
    [[nodiscard]] const sf::RenderWindow& getWindow() const;

private:
    sf::RenderWindow m_window;
};

} // namespace Engine
