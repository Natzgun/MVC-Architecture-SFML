#ifndef REVOLUTION_GAME_STATEMACHINE_HPP
#define REVOLUTION_GAME_STATEMACHINE_HPP

#include "State.hpp"
#include <memory>
#include <stack>

namespace Engine {
    using StateRef = std::unique_ptr<State>;

    class StateMachine {
    public:
        StateMachine() = default;
        ~StateMachine() = default;

        void addState(StateRef newState, bool isReplacing = true);
        void removeState();
        void processStateChanges(); // Aplica los cambios de estado pendientes

        StateRef& getActiveState(); // Obtener el estado actual
        bool empty() const; // ¿Hay estados en la pila?

    private:
        std::stack<StateRef> m_states;
        StateRef m_newState;

        bool m_isRemoving = false;
        bool m_isAdding = false;
        bool m_isReplacing = false;
    };
}

#endif //REVOLUTION_GAME_STATEMACHINE_HPP