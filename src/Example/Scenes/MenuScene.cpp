#include "Example/Scenes/MenuScene.hpp"
#include "Example/DemoScene.hpp"
#include <memory>

MenuScene::MenuScene(Engine::Context& ctx)
    : m_ctx(ctx) {
}

void MenuScene::init() {
    // Bind menu navigation actions
    m_ctx.input.bindKey("menu_up",      sf::Keyboard::Key::W);
    m_ctx.input.bindKey("menu_up",      sf::Keyboard::Key::Up);
    m_ctx.input.bindKey("menu_down",    sf::Keyboard::Key::S);
    m_ctx.input.bindKey("menu_down",    sf::Keyboard::Key::Down);
    m_ctx.input.bindKey("menu_confirm", sf::Keyboard::Key::Enter);
    m_ctx.input.bindKey("quit",         sf::Keyboard::Key::Escape);

    // Load a font -- replace with your own font file
    if (!m_font.openFromFile("assets/fonts/default.ttf")) {
        // If no font file exists, the scene will still work but text won't render.
        // Place any .ttf font at assets/fonts/default.ttf to see the menu.
    }

    // Title
    m_title.emplace(m_font, "SFML Game Template", 48);
    auto titleBounds = m_title->getLocalBounds();
    m_title->setOrigin({titleBounds.position.x + titleBounds.size.x / 2.f,
                        titleBounds.position.y + titleBounds.size.y / 2.f});
    m_title->setPosition({640.f, 200.f});
    m_title->setFillColor(sf::Color::White);

    // Menu options
    std::vector<std::string> labels = {"Start", "Exit"};
    float startY = 380.f;

    for (std::size_t i = 0; i < labels.size(); ++i) {
        m_options.emplace_back(m_font, labels[i], 32);
        auto& text = m_options.back();
        auto bounds = text.getLocalBounds();
        text.setOrigin({bounds.position.x + bounds.size.x / 2.f,
                        bounds.position.y + bounds.size.y / 2.f});
        text.setPosition({640.f, startY + static_cast<float>(i) * 60.f});
    }

    updateOptionColors();
}

void MenuScene::handleInput([[maybe_unused]] float dt) {
    if (m_ctx.input.isActionPressed("quit")) {
        m_ctx.renderer.close();
        return;
    }

    if (m_ctx.input.isActionPressed("menu_up")) {
        if (m_selected > 0) {
            m_selected--;
            updateOptionColors();
        }
    }

    if (m_ctx.input.isActionPressed("menu_down")) {
        if (m_selected < m_options.size() - 1) {
            m_selected++;
            updateOptionColors();
        }
    }

    if (m_ctx.input.isActionPressed("menu_confirm")) {
        confirm();
    }
}

void MenuScene::update([[maybe_unused]] float dt) {
    // Menu animations or effects could go here
}

void MenuScene::draw([[maybe_unused]] float interpolation) {
    if (m_title) {
        m_ctx.renderer.draw(*m_title);
    }
    for (const auto& option : m_options) {
        m_ctx.renderer.draw(option);
    }
}

void MenuScene::updateOptionColors() {
    for (std::size_t i = 0; i < m_options.size(); ++i) {
        m_options[i].setFillColor(i == m_selected ? m_selectedColor : m_normalColor);
    }
}

void MenuScene::confirm() {
    switch (m_selected) {
        case 0: // Start
            m_ctx.scenes.pushScene(
                std::make_unique<DemoScene>(m_ctx), true);
            break;
        case 1: // Exit
            m_ctx.renderer.close();
            break;
        default:
            break;
    }
}
