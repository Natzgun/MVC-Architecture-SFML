#include "Example/DemoState.hpp"

DemoState::DemoState(Engine::GameDataRef data)
    : m_data(std::move(data)) {
}

void DemoState::init() {
    m_player = sf::CircleShape(30.f);
    m_player.setFillColor(sf::Color::Cyan);
    m_player.setOrigin({30.f, 30.f});
    m_player.setPosition({640.f, 360.f});
}

void DemoState::handleInput() {
    // Process window events using SFML 3 API
    while (const auto event = m_data->window->pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            m_data->window->close();
        }
        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                m_data->window->close();
            }
        }
    }

    // Real-time input for smooth movement
    m_velocity = {0.f, 0.f};

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        m_velocity.y -= 1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        m_velocity.y += 1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        m_velocity.x -= 1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        m_velocity.x += 1.f;
    }

    // Normalize diagonal movement
    if (m_velocity.x != 0.f && m_velocity.y != 0.f) {
        m_velocity = m_velocity.normalized();
    }
}

void DemoState::update(float dt) {
    m_player.move(m_velocity * Speed * dt);
}

void DemoState::draw([[maybe_unused]] float interpolation) {
    m_data->window->draw(m_player);
}
