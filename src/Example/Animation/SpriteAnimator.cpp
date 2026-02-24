#include "Example/Animation/SpriteAnimator.hpp"

namespace Example {

void SpriteAnimator::addAnimation(const std::string& name,
                                   const std::vector<sf::IntRect>& frames,
                                   float frameDuration,
                                   bool looping) {
    m_animations[name] = Animation{frames, frameDuration, looping};
}

void SpriteAnimator::play(const std::string& name) {
    if (m_current == name && m_playing) {
        return; // Already playing this animation
    }
    m_current = name;
    m_frameIndex = 0;
    m_elapsed = 0.f;
    m_playing = true;
    m_finished = false;
}

void SpriteAnimator::stop() {
    m_playing = false;
}

void SpriteAnimator::update(float dt) {
    if (!m_playing || m_current.empty()) {
        return;
    }

    auto it = m_animations.find(m_current);
    if (it == m_animations.end() || it->second.frames.empty()) {
        return;
    }

    const Animation& anim = it->second;
    m_elapsed += dt;

    while (m_elapsed >= anim.frameDuration) {
        m_elapsed -= anim.frameDuration;
        m_frameIndex++;

        if (m_frameIndex >= anim.frames.size()) {
            if (anim.looping) {
                m_frameIndex = 0;
            } else {
                m_frameIndex = anim.frames.size() - 1;
                m_playing = false;
                m_finished = true;
                break;
            }
        }
    }
}

void SpriteAnimator::applyToSprite(sf::Sprite& sprite) const {
    if (m_current.empty()) {
        return;
    }

    auto it = m_animations.find(m_current);
    if (it == m_animations.end() || it->second.frames.empty()) {
        return;
    }

    sprite.setTextureRect(it->second.frames[m_frameIndex]);
}

bool SpriteAnimator::isFinished() const {
    return m_finished;
}

const std::string& SpriteAnimator::currentAnimation() const {
    return m_current;
}

std::size_t SpriteAnimator::currentFrame() const {
    return m_frameIndex;
}

} // namespace Example
