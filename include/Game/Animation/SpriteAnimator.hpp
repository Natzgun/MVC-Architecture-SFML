#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>
#include <vector>

namespace Game {

/// A single animation: a sequence of texture sub-rectangles at a given speed.
struct Animation {
    std::vector<sf::IntRect> frames; ///< Source rectangles in the sprite sheet.
    float frameDuration = 0.1f;      ///< Seconds per frame.
    bool looping = true;             ///< Whether the animation loops.
};

/// Frame-based sprite sheet animator.
///
/// Manages multiple named animations for a single sprite. Each animation
/// is a sequence of IntRects (regions of a sprite sheet) played at a
/// configurable speed.
///
/// Usage:
/// @code
///   SpriteAnimator animator;
///   animator.addAnimation("idle", { {0,0,32,32}, {32,0,32,32} }, 0.15f);
///   animator.addAnimation("run",  { {0,32,32,32}, {32,32,32,32}, {64,32,32,32} }, 0.1f);
///   animator.play("idle");
///   // In update loop:
///   animator.update(dt);
///   animator.applyToSprite(mySprite);
/// @endcode
class SpriteAnimator {
public:
    SpriteAnimator() = default;

    /// Register a named animation.
    /// @param name         Unique identifier for this animation.
    /// @param frames       Ordered list of source rectangles in the sprite sheet.
    /// @param frameDuration Seconds each frame is displayed.
    /// @param looping      Whether the animation repeats.
    void addAnimation(const std::string& name,
                      const std::vector<sf::IntRect>& frames,
                      float frameDuration = 0.1f,
                      bool looping = true);

    /// Start playing the named animation. Resets to frame 0 if it's a different
    /// animation than the current one.
    /// @param name The animation to play.
    void play(const std::string& name);

    /// Stop the current animation (stays on current frame).
    void stop();

    /// Advance the animation timer by dt seconds.
    /// @param dt Delta time in seconds.
    void update(float dt);

    /// Apply the current animation frame as the sprite's texture rect.
    /// @param sprite The sprite to modify.
    void applyToSprite(sf::Sprite& sprite) const;

    /// Check if the current animation has finished (only relevant for non-looping).
    [[nodiscard]] bool isFinished() const;

    /// Get the name of the currently playing animation (empty if none).
    [[nodiscard]] const std::string& currentAnimation() const;

    /// Get the current frame index within the active animation.
    [[nodiscard]] std::size_t currentFrame() const;

private:
    std::unordered_map<std::string, Animation> m_animations;
    std::string m_current;
    std::size_t m_frameIndex = 0;
    float m_elapsed = 0.f;
    bool m_playing = false;
    bool m_finished = false;
};

} // namespace Game
