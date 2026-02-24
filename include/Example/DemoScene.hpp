#pragma once

#include "Engine/Scene/Scene.hpp"
#include "Engine/Core/Application.hpp"
#include <SFML/Graphics.hpp>

/// Example scene that demonstrates how to use the modular engine template.
/// Renders a movable circle controlled with WASD keys (action-mapped).
/// Press Escape or close the window to exit.
///
/// This file is meant as a starting point -- replace or modify it
/// to build your own game.
class DemoScene : public Engine::Scene {
public:
    explicit DemoScene(Engine::Context& ctx);
    ~DemoScene() override = default;

    void init() override;
    void handleInput(float dt) override;
    void update(float dt) override;
    void draw(float interpolation) override;

private:
    Engine::Context& m_ctx;

    sf::CircleShape m_player;
    sf::Vector2f m_velocity{0.f, 0.f};

    static constexpr float Speed = 200.f; // pixels per second
};
