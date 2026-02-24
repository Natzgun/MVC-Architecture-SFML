#pragma once

#include "Engine/Scene/Scene.hpp"
#include "Engine/Core/Application.hpp"
#include <SFML/Graphics.hpp>
#include <optional>

/// Pause overlay scene.
///
/// Pushed on top of the gameplay scene (which gets paused).
/// Displays "PAUSED" text and options to resume or quit.
/// Navigate with Up/Down, confirm with Enter, or press Escape to resume.
class PauseScene : public Engine::Scene {
public:
    explicit PauseScene(Engine::Context& ctx);
    ~PauseScene() override = default;

    void init() override;
    void handleInput(float dt) override;
    void update(float dt) override;
    void draw(float interpolation) override;

private:
    Engine::Context& m_ctx;

    sf::Font m_font;
    std::optional<sf::Text> m_title;
    std::optional<sf::Text> m_resumeText;
    std::optional<sf::Text> m_quitText;
    sf::RectangleShape m_overlay; // Semi-transparent background

    std::size_t m_selected = 0;
    sf::Color m_normalColor  = sf::Color(180, 180, 180);
    sf::Color m_selectedColor = sf::Color::White;

    void updateOptionColors();
};
