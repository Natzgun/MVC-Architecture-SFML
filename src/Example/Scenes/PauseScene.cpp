#include "Example/Scenes/PauseScene.hpp"

PauseScene::PauseScene(Engine::Context& ctx)
    : m_ctx(ctx) {
}

void PauseScene::init() {
    m_ctx.input.bindKey("pause_up",      sf::Keyboard::Key::W);
    m_ctx.input.bindKey("pause_up",      sf::Keyboard::Key::Up);
    m_ctx.input.bindKey("pause_down",    sf::Keyboard::Key::S);
    m_ctx.input.bindKey("pause_down",    sf::Keyboard::Key::Down);
    m_ctx.input.bindKey("pause_confirm", sf::Keyboard::Key::Enter);
    m_ctx.input.bindKey("pause_back",    sf::Keyboard::Key::Escape);

    // Semi-transparent dark overlay
    auto size = m_ctx.renderer.getSize();
    m_overlay.setSize({static_cast<float>(size.x), static_cast<float>(size.y)});
    m_overlay.setFillColor(sf::Color(0, 0, 0, 150));

    // Load font
    if (!m_font.openFromFile("assets/fonts/default.ttf")) {
        // Same fallback as MenuScene -- place a .ttf at assets/fonts/default.ttf
    }

    float centerX = static_cast<float>(size.x) / 2.f;

    // Title
    m_title.emplace(m_font, "PAUSED", 48);
    auto titleBounds = m_title->getLocalBounds();
    m_title->setOrigin({titleBounds.position.x + titleBounds.size.x / 2.f,
                        titleBounds.position.y + titleBounds.size.y / 2.f});
    m_title->setPosition({centerX, 250.f});
    m_title->setFillColor(sf::Color::White);

    // Resume option
    m_resumeText.emplace(m_font, "Resume", 32);
    auto rBounds = m_resumeText->getLocalBounds();
    m_resumeText->setOrigin({rBounds.position.x + rBounds.size.x / 2.f,
                             rBounds.position.y + rBounds.size.y / 2.f});
    m_resumeText->setPosition({centerX, 380.f});

    // Quit option
    m_quitText.emplace(m_font, "Quit", 32);
    auto qBounds = m_quitText->getLocalBounds();
    m_quitText->setOrigin({qBounds.position.x + qBounds.size.x / 2.f,
                           qBounds.position.y + qBounds.size.y / 2.f});
    m_quitText->setPosition({centerX, 440.f});

    updateOptionColors();
}

void PauseScene::handleInput([[maybe_unused]] float dt) {
    // Escape resumes immediately
    if (m_ctx.input.isActionPressed("pause_back")) {
        m_ctx.scenes.popScene();
        return;
    }

    if (m_ctx.input.isActionPressed("pause_up")) {
        if (m_selected > 0) {
            m_selected--;
            updateOptionColors();
        }
    }

    if (m_ctx.input.isActionPressed("pause_down")) {
        if (m_selected < 1) {
            m_selected++;
            updateOptionColors();
        }
    }

    if (m_ctx.input.isActionPressed("pause_confirm")) {
        if (m_selected == 0) {
            // Resume
            m_ctx.scenes.popScene();
        } else {
            // Quit
            m_ctx.renderer.close();
        }
    }
}

void PauseScene::update([[maybe_unused]] float dt) {
    // Pause animations or effects could go here
}

void PauseScene::draw([[maybe_unused]] float interpolation) {
    // Draw overlay on top of whatever scene is below
    m_ctx.renderer.setView(m_ctx.renderer.getDefaultView());
    m_ctx.renderer.draw(m_overlay);
    if (m_title)      m_ctx.renderer.draw(*m_title);
    if (m_resumeText) m_ctx.renderer.draw(*m_resumeText);
    if (m_quitText)   m_ctx.renderer.draw(*m_quitText);
}

void PauseScene::updateOptionColors() {
    if (m_resumeText) m_resumeText->setFillColor(m_selected == 0 ? m_selectedColor : m_normalColor);
    if (m_quitText)   m_quitText->setFillColor(m_selected == 1 ? m_selectedColor : m_normalColor);
}
