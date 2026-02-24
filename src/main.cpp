#include "Core/Game.hpp"
#include "States/GameState.hpp"
#include <memory>

int main() {
    // Inicializar el Motor Base (1280x720)
    Engine::Game game(1280, 720, "Examen MVC - Arquitectura Escalable");

    // Inyectar el primer estado en la máquina (Tu MVC)
    game.getContext()->machine->addState(
        std::make_unique<Engine::GameState>(game.getContext())
    );

    // Correr el bucle principal a 60 FPS fijos
    game.run();
    return 0;
}