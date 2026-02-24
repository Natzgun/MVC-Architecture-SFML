#include "Game/Physics/Collision.hpp"
#include <algorithm>
#include <cmath>

namespace Game::Collision {

CollisionResult checkAABB(const sf::FloatRect& a, const sf::FloatRect& b) {
    CollisionResult result;

    // Compute centers and half-sizes
    float ax = a.position.x + a.size.x / 2.f;
    float ay = a.position.y + a.size.y / 2.f;
    float bx = b.position.x + b.size.x / 2.f;
    float by = b.position.y + b.size.y / 2.f;

    float halfWidthA  = a.size.x / 2.f;
    float halfHeightA = a.size.y / 2.f;
    float halfWidthB  = b.size.x / 2.f;
    float halfHeightB = b.size.y / 2.f;

    float dx = bx - ax;
    float dy = by - ay;

    float overlapX = halfWidthA + halfWidthB - std::abs(dx);
    float overlapY = halfHeightA + halfHeightB - std::abs(dy);

    if (overlapX <= 0.f || overlapY <= 0.f) {
        return result; // No collision
    }

    result.colliding = true;

    // Minimum translation vector: resolve along the axis of least overlap
    if (overlapX < overlapY) {
        result.overlap.x = (dx > 0.f) ? overlapX : -overlapX;
        result.overlap.y = 0.f;
    } else {
        result.overlap.x = 0.f;
        result.overlap.y = (dy > 0.f) ? overlapY : -overlapY;
    }

    return result;
}

bool intersects(const sf::FloatRect& a, const sf::FloatRect& b) {
    return a.findIntersection(b).has_value();
}

bool contains(sf::Vector2f point, const sf::FloatRect& rect) {
    return rect.contains(point);
}

} // namespace Game::Collision
