#include "States/StateMachine.hpp"

namespace Engine {
    void StateMachine::addState(StateRef newState, bool isReplacing) {
        m_isAdding = true;
        m_isReplacing = isReplacing;
        m_newState = std::move(newState);
    }

    void StateMachine::removeState() {
        m_isRemoving = true;
    }

    void StateMachine::processStateChanges() {
        // ¿Debemos quitar el estado actual? (Para volver a la pantalla anterior)
        if (m_isRemoving && !m_states.empty()) {
            m_states.pop();
            if (!m_states.empty()) {
                m_states.top()->resume();
            }
            m_isRemoving = false;
        }

        // ¿Debemos añadir un estado nuevo? (Ir a una nueva pantalla)
        if (m_isAdding) {
            if (!m_states.empty()) {
                if (m_isReplacing) {
                    m_states.pop(); // Destruye el estado anterior
                } else {
                    m_states.top()->pause(); // Pausa el estado anterior, pero lo mantiene
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
}