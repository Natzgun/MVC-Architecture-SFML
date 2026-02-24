#include "Core/Game.hpp"
#include "Example/DemoState.hpp"
#include <memory>

int main() {
    Engine::Game game(1280, 720, "SFML Game Template");

    game.getContext()->machine->pushState(
        std::make_unique<DemoState>(game.getContext()));

    game.run();
    return 0;
}
