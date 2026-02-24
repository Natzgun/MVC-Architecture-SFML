#include "States/StateMachine.hpp"

namespace Engine {

void StateMachine::pushState(StateRef newState, bool isReplacing) {
    m_isAdding = true;
    m_isReplacing = isReplacing;
    m_newState = std::move(newState);
}

void StateMachine::popState() {
    m_isRemoving = true;
}

void StateMachine::processStateChanges() {
    // Handle removal request
    if (m_isRemoving && !m_states.empty()) {
        m_states.pop();
        if (!m_states.empty()) {
            m_states.top()->resume();
        }
        m_isRemoving = false;
    }

    // Handle addition request
    if (m_isAdding) {
        if (!m_states.empty()) {
            if (m_isReplacing) {
                m_states.pop();
            } else {
                m_states.top()->pause();
            }
        }

        m_states.push(std::move(m_newState));
        m_states.top()->init();
        m_isAdding = false;
    }
}

StateRef& StateMachine::getActiveState() {
    return m_states.top();
}

bool StateMachine::empty() const {
    return m_states.empty();
}

} // namespace Engine
