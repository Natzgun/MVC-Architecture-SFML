#include "Game/UI/HUD.hpp"

namespace Game {

void HUD::setVisible(bool visible) {
    m_visible = visible;
}

bool HUD::isVisible() const {
    return m_visible;
}

} // namespace Game
