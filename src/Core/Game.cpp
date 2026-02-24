#include "Core/Game.hpp"
#include "States/State.hpp"

namespace Engine {
    Game::Game(int width, int height, const std::string& title) {
        m_data->window = std::make_unique<sf::RenderWindow>(sf::VideoMode(width, height), title);
        m_data->window->setFramerateLimit(60);
        m_data->machine = std::make_unique<StateMachine>();
    }

    void Game::run() {
        float newTime, frameTime, interpolation;
        float currentTime = m_clock.getElapsedTime().asSeconds();
        float accumulator = 0.0f;

        // Bucle Principal (Fixed Time Step - Estándar para videojuegos)
        while (m_data->window->isOpen() && !m_data->machine->empty()) {
            
            // 1. Aplicar cambios de estado pendientes (ej. pasar del Menu a Juego)
            m_data->machine->processStateChanges();

            // Lógica de Delta Time Fijo
            newTime = m_clock.getElapsedTime().asSeconds();
            frameTime = newTime - currentTime;

            // Evitar problemas de física si el frame se retrasa mucho ("Spiraling of Death")
            if (frameTime > 0.25f) frameTime = 0.25f;

            currentTime = newTime;
            accumulator += frameTime;

            // 2. Procesar Entrada (Gestión de eventos y teclado)
            m_data->machine->getActiveState()->handleInput();

            // 3. Actualizar Lógica a ritmo constante
            while (accumulator >= dt) {
                m_data->machine->getActiveState()->update(dt);
                accumulator -= dt;
            }

            // Interpolación para un dibujo más suave
            interpolation = accumulator / dt;

            // 4. Dibujar Pantalla
            m_data->window->clear();
            m_data->machine->getActiveState()->draw(interpolation);
            m_data->window->display();
        }
    }
}