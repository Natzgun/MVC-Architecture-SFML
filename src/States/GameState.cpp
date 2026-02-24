#include "States/GameState.hpp"

namespace Engine {

    GameState::GameState(GameDataRef data) : m_data(data) {}

    void GameState::init() {
        // 1. Creamos las piezas
        m_model = std::make_unique<Model>();
        m_view = std::make_unique<View>(m_data);
        
        // 2. Las inyectamos en el controlador (Ensamblaje)
        m_controller = std::make_unique<Controller>(m_model.get(), m_view.get());
    }

    void GameState::handleInput() {
        sf::Event event;
        // Procesamos eventos de la ventana desde el estado
        while (m_data->window->pollEvent(event)) {
            if (sf::Event::Closed == event.type) {
                m_data->window->close();
            }
        }
        
        // Delegamos la lectura de teclado al controlador (tu MVC)
        m_controller->procesarEntrada();
    }

    void GameState::update(float dt) {
        // En una implementación real, pasarías el 'dt' (delta time) al modelo para física
        m_controller->actualizar();
    }

    void GameState::draw(float dt) {
        // Delegamos el renderizado al controlador (tu MVC)
        m_controller->dibujar();
    }
}