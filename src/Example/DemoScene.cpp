#include "Example/DemoScene.hpp"

DemoScene::DemoScene(Engine::Context& ctx)
    : m_ctx(ctx) {
}

void DemoScene::init() {
    // Set up the player shape
    m_player = sf::CircleShape(30.f);
    m_player.setFillColor(sf::Color::Cyan);
    m_player.setOrigin({30.f, 30.f});
    m_player.setPosition({640.f, 360.f});

    // Bind input actions -- game code uses logical names, not raw keys.
    // This makes rebinding trivial (just change the binding, not the logic).
    m_ctx.input.bindKey("move_up",    sf::Keyboard::Key::W);
    m_ctx.input.bindKey("move_up",    sf::Keyboard::Key::Up);
    m_ctx.input.bindKey("move_down",  sf::Keyboard::Key::S);
    m_ctx.input.bindKey("move_down",  sf::Keyboard::Key::Down);
    m_ctx.input.bindKey("move_left",  sf::Keyboard::Key::A);
    m_ctx.input.bindKey("move_left",  sf::Keyboard::Key::Left);
    m_ctx.input.bindKey("move_right", sf::Keyboard::Key::D);
    m_ctx.input.bindKey("move_right", sf::Keyboard::Key::Right);
    m_ctx.input.bindKey("quit",       sf::Keyboard::Key::Escape);
}

void DemoScene::handleInput([[maybe_unused]] float dt) {
    // Check for quit via action mapping
    if (m_ctx.input.isActionPressed("quit")) {
        m_ctx.renderer.close();
        return;
    }

    // Compute movement direction from action bindings
    m_velocity = {0.f, 0.f};

    if (m_ctx.input.isActionHeld("move_up")) {
        m_velocity.y -= 1.f;
    }
    if (m_ctx.input.isActionHeld("move_down")) {
        m_velocity.y += 1.f;
    }
    if (m_ctx.input.isActionHeld("move_left")) {
        m_velocity.x -= 1.f;
    }
    if (m_ctx.input.isActionHeld("move_right")) {
        m_velocity.x += 1.f;
    }

    // Normalize diagonal movement
    if (m_velocity.x != 0.f && m_velocity.y != 0.f) {
        m_velocity = m_velocity.normalized();
    }
}

void DemoScene::update(float dt) {
    m_player.move(m_velocity * Speed * dt);
}

void DemoScene::draw([[maybe_unused]] float interpolation) {
    m_ctx.renderer.draw(m_player);
}
