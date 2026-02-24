#pragma once

#include <SFML/Graphics.hpp>

namespace Engine { class Renderer; }

namespace Example {

/// 2D camera that follows a target position with optional smoothing and bounds.
///
/// Wraps an sf::View and provides target-following behavior with
/// configurable lerp speed and world boundary clamping.
///
/// Usage:
/// @code
///   Camera camera({1280.f, 720.f});
///   camera.setWorldBounds({0.f, 0.f, 3000.f, 2000.f});
///   camera.setTarget(player.getPosition());
///   // In update:
///   camera.update(dt);
///   camera.applyTo(renderer);
/// @endcode
class Camera {
public:
    /// Create a camera with the given viewport size.
    /// @param viewSize The visible area size in world units (typically window size).
    explicit Camera(sf::Vector2f viewSize);

    /// Set the position the camera should follow.
    /// @param target World position to center on.
    void setTarget(sf::Vector2f target);

    /// Immediately snap the camera to the target (no smoothing).
    void snapToTarget();

    /// Set the interpolation speed for smooth following.
    /// 1.0 = instant, lower = smoother/slower. Default is 5.0.
    /// @param speed Lerp speed (higher = faster catch-up).
    void setSmoothSpeed(float speed);

    /// Set world boundaries so the camera doesn't show outside the map.
    /// Pass a zero-size rect to disable bounds clamping.
    /// @param bounds World rectangle to clamp the view within.
    void setWorldBounds(const sf::FloatRect& bounds);

    /// Update the camera position (call once per frame in update).
    /// @param dt Delta time in seconds.
    void update(float dt);

    /// Apply this camera's view to the renderer.
    /// @param renderer The engine renderer.
    void applyTo(Engine::Renderer& renderer) const;

    /// Set the zoom factor (1.0 = normal, < 1 = zoom in, > 1 = zoom out).
    void setZoom(float factor);

    /// Get the current camera center position.
    [[nodiscard]] sf::Vector2f getCenter() const;

    /// Get the underlying sf::View (e.g., for coordinate mapping).
    [[nodiscard]] const sf::View& getView() const;

private:
    sf::View m_view;
    sf::Vector2f m_target{0.f, 0.f};
    sf::Vector2f m_viewSize;
    sf::FloatRect m_worldBounds{};
    float m_smoothSpeed = 5.f;
    bool m_hasBounds = false;

    void clampToBounds();
};

} // namespace Example
