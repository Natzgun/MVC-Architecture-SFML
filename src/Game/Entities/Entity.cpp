#include "Game/Entities/Entity.hpp"

namespace Game {

Entity::Entity(sf::Vector2f position, sf::Vector2f size)
    : m_position(position), m_size(size) {
}

void Entity::update(float dt) {
    m_position += m_velocity * dt;
}

void Entity::setPosition(sf::Vector2f pos) {
    m_position = pos;
}

void Entity::move(sf::Vector2f offset) {
    m_position += offset;
}

sf::Vector2f Entity::getPosition() const {
    return m_position;
}

void Entity::setVelocity(sf::Vector2f vel) {
    m_velocity = vel;
}

sf::Vector2f Entity::getVelocity() const {
    return m_velocity;
}

void Entity::setSize(sf::Vector2f size) {
    m_size = size;
}

sf::Vector2f Entity::getSize() const {
    return m_size;
}

sf::FloatRect Entity::getBounds() const {
    return sf::FloatRect(m_position, m_size);
}

void Entity::setAlive(bool alive) {
    m_alive = alive;
}

bool Entity::isAlive() const {
    return m_alive;
}

} // namespace Game
