#include "Example/UI/HUD.hpp"

namespace Example {

void HUD::setVisible(bool visible) {
    m_visible = visible;
}

bool HUD::isVisible() const {
    return m_visible;
}

} // namespace Example
