#include "Engine/Input/InputManager.hpp"
#include "Engine/Graphics/Renderer.hpp"
#include <algorithm>

namespace Engine {

void InputManager::pollEvents(Renderer& renderer) {
    // Clear per-frame state
    m_pressedThisFrame.clear();
    m_releasedThisFrame.clear();
    m_closeRequested = false;

    auto& window = renderer.getWindow();

    while (const auto event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            m_closeRequested = true;
        }

        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            m_pressedThisFrame.push_back(keyPressed->code);
        }

        if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>()) {
            m_releasedThisFrame.push_back(keyReleased->code);
        }
    }
}

void InputManager::bindKey(const Action& action, sf::Keyboard::Key key) {
    auto& keys = m_bindings[action];
    // Avoid duplicate bindings
    if (std::find(keys.begin(), keys.end(), key) == keys.end()) {
        keys.push_back(key);
    }
}

void InputManager::unbindAction(const Action& action) {
    m_bindings.erase(action);
}

void InputManager::clearBindings() {
    m_bindings.clear();
}

bool InputManager::isActionHeld(const Action& action) const {
    auto it = m_bindings.find(action);
    if (it == m_bindings.end()) return false;

    for (const auto& key : it->second) {
        if (sf::Keyboard::isKeyPressed(key)) {
            return true;
        }
    }
    return false;
}

bool InputManager::isKeyHeld(sf::Keyboard::Key key) {
    return sf::Keyboard::isKeyPressed(key);
}

bool InputManager::isMouseButtonHeld(sf::Mouse::Button button) {
    return sf::Mouse::isButtonPressed(button);
}

sf::Vector2i InputManager::getMousePosition(const Renderer& renderer) const {
    return sf::Mouse::getPosition(renderer.getWindow());
}

bool InputManager::isActionPressed(const Action& action) const {
    auto it = m_bindings.find(action);
    if (it == m_bindings.end()) return false;

    for (const auto& key : it->second) {
        if (std::find(m_pressedThisFrame.begin(), m_pressedThisFrame.end(), key)
            != m_pressedThisFrame.end()) {
            return true;
        }
    }
    return false;
}

bool InputManager::isActionReleased(const Action& action) const {
    auto it = m_bindings.find(action);
    if (it == m_bindings.end()) return false;

    for (const auto& key : it->second) {
        if (std::find(m_releasedThisFrame.begin(), m_releasedThisFrame.end(), key)
            != m_releasedThisFrame.end()) {
            return true;
        }
    }
    return false;
}

bool InputManager::isWindowCloseRequested() const {
    return m_closeRequested;
}

} // namespace Engine
