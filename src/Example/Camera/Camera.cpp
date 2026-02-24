#include "Example/Camera/Camera.hpp"
#include "Engine/Graphics/Renderer.hpp"
#include <algorithm>

namespace Example {

Camera::Camera(sf::Vector2f viewSize)
    : m_view(sf::FloatRect({0.f, 0.f}, viewSize))
    , m_viewSize(viewSize) {
}

void Camera::setTarget(sf::Vector2f target) {
    m_target = target;
}

void Camera::snapToTarget() {
    m_view.setCenter(m_target);
    clampToBounds();
}

void Camera::setSmoothSpeed(float speed) {
    m_smoothSpeed = speed;
}

void Camera::setWorldBounds(const sf::FloatRect& bounds) {
    m_worldBounds = bounds;
    m_hasBounds = (bounds.size.x > 0.f && bounds.size.y > 0.f);
}

void Camera::update(float dt) {
    sf::Vector2f current = m_view.getCenter();
    // Lerp toward target
    float t = std::min(1.f, m_smoothSpeed * dt);
    sf::Vector2f newCenter = current + (m_target - current) * t;
    m_view.setCenter(newCenter);
    clampToBounds();
}

void Camera::applyTo(Engine::Renderer& renderer) const {
    renderer.setView(m_view);
}

void Camera::setZoom(float factor) {
    m_view.setSize(m_viewSize * factor);
}

sf::Vector2f Camera::getCenter() const {
    return m_view.getCenter();
}

const sf::View& Camera::getView() const {
    return m_view;
}

void Camera::clampToBounds() {
    if (!m_hasBounds) return;

    sf::Vector2f halfSize = m_view.getSize() / 2.f;
    sf::Vector2f center = m_view.getCenter();

    float minX = m_worldBounds.position.x + halfSize.x;
    float maxX = m_worldBounds.position.x + m_worldBounds.size.x - halfSize.x;
    float minY = m_worldBounds.position.y + halfSize.y;
    float maxY = m_worldBounds.position.y + m_worldBounds.size.y - halfSize.y;

    // If the view is larger than the world, center it
    if (minX > maxX) {
        center.x = m_worldBounds.position.x + m_worldBounds.size.x / 2.f;
    } else {
        center.x = std::clamp(center.x, minX, maxX);
    }

    if (minY > maxY) {
        center.y = m_worldBounds.position.y + m_worldBounds.size.y / 2.f;
    } else {
        center.y = std::clamp(center.y, minY, maxY);
    }

    m_view.setCenter(center);
}

} // namespace Example
