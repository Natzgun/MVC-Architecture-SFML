#pragma once

#include <SFML/Graphics.hpp>

namespace Engine { class Renderer; }

namespace Example {

/// Base class for all game entities.
///
/// Provides position, velocity, bounding box, and active state.
/// Derived classes override update() and draw() to add behavior.
/// Entities that are not alive are skipped during update/draw loops.
class Entity {
public:
    Entity() = default;
    explicit Entity(sf::Vector2f position, sf::Vector2f size = {0.f, 0.f});
    virtual ~Entity() = default;

    /// Update entity logic each fixed timestep.
    /// @param dt Fixed delta time in seconds.
    virtual void update(float dt);

    /// Draw the entity through the renderer.
    /// @param renderer The engine renderer.
    virtual void draw(Engine::Renderer& renderer) = 0;

    // --- Position and movement ---
    void setPosition(sf::Vector2f pos);
    void move(sf::Vector2f offset);
    [[nodiscard]] sf::Vector2f getPosition() const;

    void setVelocity(sf::Vector2f vel);
    [[nodiscard]] sf::Vector2f getVelocity() const;

    // --- Bounding box ---
    void setSize(sf::Vector2f size);
    [[nodiscard]] sf::Vector2f getSize() const;
    [[nodiscard]] sf::FloatRect getBounds() const;

    // --- Lifecycle ---
    void setAlive(bool alive);
    [[nodiscard]] bool isAlive() const;

protected:
    sf::Vector2f m_position{0.f, 0.f};
    sf::Vector2f m_velocity{0.f, 0.f};
    sf::Vector2f m_size{0.f, 0.f};
    bool m_alive = true;
};

} // namespace Example
