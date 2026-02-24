#include "Core/Game.hpp"

namespace Engine {

Game::Game(unsigned int width, unsigned int height, const std::string& title) {
    m_data->window = std::make_unique<sf::RenderWindow>(
        sf::VideoMode({width, height}), title);
    m_data->window->setFramerateLimit(60);
    m_data->machine = std::make_unique<StateMachine>();
}

void Game::run() {
    float currentTime = m_clock.getElapsedTime().asSeconds();
    float accumulator = 0.0f;

    while (m_data->window->isOpen() && !m_data->machine->empty()) {
        // 1. Apply pending state changes (e.g., menu -> gameplay)
        m_data->machine->processStateChanges();

        // Fixed timestep accumulation
        float newTime = m_clock.getElapsedTime().asSeconds();
        float frameTime = newTime - currentTime;

        // Clamp to avoid spiral of death
        if (frameTime > 0.25f)
            frameTime = 0.25f;

        currentTime = newTime;
        accumulator += frameTime;

        // 2. Handle input (events + real-time)
        m_data->machine->getActiveState()->handleInput();

        // 3. Fixed-rate logic updates
        while (accumulator >= dt) {
            m_data->machine->getActiveState()->update(dt);
            accumulator -= dt;
        }

        // 4. Render with interpolation
        float interpolation = accumulator / dt;
        m_data->window->clear();
        m_data->machine->getActiveState()->draw(interpolation);
        m_data->window->display();
    }
}

} // namespace Engine
