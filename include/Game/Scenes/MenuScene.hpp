#pragma once

#include "Engine/Scene/Scene.hpp"
#include "Engine/Core/Application.hpp"
#include <SFML/Graphics.hpp>
#include <optional>
#include <vector>
#include <string>

/// Main menu scene with selectable options.
///
/// Displays a title and a vertical list of menu items (Start, Exit, etc.).
/// Navigate with Up/Down arrows or W/S, confirm with Enter.
/// Push your gameplay scene from the "Start" option.
class MenuScene : public Engine::Scene {
public:
    explicit MenuScene(Engine::Context& ctx);
    ~MenuScene() override = default;

    void init() override;
    void handleInput(float dt) override;
    void update(float dt) override;
    void draw(float interpolation) override;

private:
    Engine::Context& m_ctx;

    sf::Font m_font;
    std::optional<sf::Text> m_title;
    std::vector<sf::Text> m_options;
    std::size_t m_selected = 0;

    sf::Color m_normalColor  = sf::Color(180, 180, 180);
    sf::Color m_selectedColor = sf::Color::White;

    void updateOptionColors();
    void confirm();
};
