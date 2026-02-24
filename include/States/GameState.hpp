#ifndef REVOLUTION_GAME_GAMESTATE_HPP
#define REVOLUTION_GAME_GAMESTATE_HPP

#include "States/State.hpp"
#include "Core/Game.hpp"
#include "Game/Controller/Controller.h"
#include <memory>

namespace Engine {

    // Ejemplo de una escena (estado) que utiliza tu arquitectura MVC
    class GameState : public State {
    public:
        // El estado necesita el contexto global (GameDataRef) para pasarlo a la Vista
        explicit GameState(GameDataRef data);
        ~GameState() override = default;

        void init() override;
        void handleInput() override;
        void update(float dt) override;
        void draw(float dt) override;

    private:
        GameDataRef m_data;
        
        // El estado ahora es el "dueño" de los componentes y los ensambla
        std::unique_ptr<Model> m_model;
        std::unique_ptr<View> m_view;
        std::unique_ptr<Controller> m_controller;
    };
}

#endif //REVOLUTION_GAME_GAMESTATE_HPP