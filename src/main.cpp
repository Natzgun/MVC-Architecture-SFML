#include "Engine/Core/Application.hpp"
#include "Example/DemoScene.hpp"
#include <memory>

int main() {
    Engine::Application app(1280, 720, "SFML Game Template");

    app.context().scenes.pushScene(
        std::make_unique<DemoScene>(app.context()));

    app.run();
    return 0;
}
