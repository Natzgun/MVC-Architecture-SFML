#pragma once

#include <SFML/Graphics.hpp>

namespace Engine { class Renderer; }

namespace Example {

/// Base class for heads-up display overlays.
///
/// HUD elements are drawn in screen space (using the default view),
/// independent of the game camera. Derive from this class to create
/// score displays, health bars, minimaps, etc.
///
/// Usage:
/// @code
///   class ScoreHUD : public HUD {
///   public:
///       void update(float dt) override { /* update score text */ }
///       void draw(Engine::Renderer& renderer) override {
///           renderer.draw(m_scoreText);
///       }
///   };
/// @endcode
class HUD {
public:
    HUD() = default;
    virtual ~HUD() = default;

    /// Update HUD state (animations, timers, etc.).
    /// @param dt Delta time in seconds.
    virtual void update(float dt) = 0;

    /// Draw HUD elements through the renderer.
    /// The caller is responsible for setting the default view before calling this.
    /// @param renderer The engine renderer.
    virtual void draw(Engine::Renderer& renderer) = 0;

    /// Show or hide the HUD.
    void setVisible(bool visible);

    /// Check if the HUD is visible.
    [[nodiscard]] bool isVisible() const;

protected:
    bool m_visible = true;
};

} // namespace Example
