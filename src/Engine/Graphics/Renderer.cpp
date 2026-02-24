#include "Engine/Graphics/Renderer.hpp"

namespace Engine {

Renderer::Renderer(unsigned int width, unsigned int height, const std::string& title)
    : m_window(sf::VideoMode({width, height}), title) {
}

void Renderer::clear(sf::Color color) {
    m_window.clear(color);
}

void Renderer::draw(const sf::Drawable& drawable) {
    m_window.draw(drawable);
}

void Renderer::draw(const sf::Drawable& drawable, const sf::RenderStates& states) {
    m_window.draw(drawable, states);
}

void Renderer::display() {
    m_window.display();
}

bool Renderer::isOpen() const {
    return m_window.isOpen();
}

void Renderer::close() {
    m_window.close();
}

void Renderer::setFramerateLimit(unsigned int limit) {
    m_window.setFramerateLimit(limit);
}

sf::Vector2u Renderer::getSize() const {
    return m_window.getSize();
}

void Renderer::setView(const sf::View& view) {
    m_window.setView(view);
}

const sf::View& Renderer::getView() const {
    return m_window.getView();
}

const sf::View& Renderer::getDefaultView() const {
    return m_window.getDefaultView();
}

sf::RenderWindow& Renderer::getWindow() {
    return m_window;
}

const sf::RenderWindow& Renderer::getWindow() const {
    return m_window;
}

} // namespace Engine
