#pragma once

#include "States/State.hpp"
#include "Core/Game.hpp"
#include <SFML/Graphics.hpp>

/// Example state that demonstrates how to use the engine template.
/// Renders a movable circle controlled with WASD keys.
/// Press Escape or close the window to exit.
///
/// This file is meant as a starting point -- replace or modify it
/// to build your own game.
class DemoState : public Engine::State {
public:
    explicit DemoState(Engine::GameDataRef data);
    ~DemoState() override = default;

    void init() override;
    void handleInput() override;
    void update(float dt) override;
    void draw(float interpolation) override;

private:
    Engine::GameDataRef m_data;

    sf::CircleShape m_player;
    sf::Vector2f m_velocity{0.f, 0.f};

    static constexpr float Speed = 200.f; // pixels per second
};
