#pragma once

#include <SFML/Graphics.hpp>

namespace Game {

/// Result of a collision check between two AABBs.
struct CollisionResult {
    bool colliding = false;      ///< Whether the two rects overlap.
    sf::Vector2f overlap{0.f, 0.f}; ///< Minimum translation vector to resolve.
};

/// Axis-Aligned Bounding Box collision utilities.
///
/// Provides detection and resolution for rectangular entities.
/// Sufficient for most 2D games (platformers, RPGs, shooters).
/// For circle collision, pixel-perfect, or tilemap queries, extend as needed.
namespace Collision {

    /// Check if two rectangles overlap and compute the minimum overlap vector.
    /// The overlap vector points from A toward B (push A by -overlap to resolve).
    /// @param a First bounding box.
    /// @param b Second bounding box.
    /// @return CollisionResult with overlap data.
    CollisionResult checkAABB(const sf::FloatRect& a, const sf::FloatRect& b);

    /// Simple boolean overlap check (faster if you don't need resolution).
    /// @param a First bounding box.
    /// @param b Second bounding box.
    /// @return True if the rectangles intersect.
    bool intersects(const sf::FloatRect& a, const sf::FloatRect& b);

    /// Check if a point is inside a rectangle.
    /// @param point The point to test.
    /// @param rect The bounding rectangle.
    /// @return True if the point is inside the rectangle.
    bool contains(sf::Vector2f point, const sf::FloatRect& rect);

} // namespace Collision
} // namespace Game
