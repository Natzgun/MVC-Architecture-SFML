#pragma once

#include "State.hpp"
#include <memory>
#include <stack>

namespace Engine {

using StateRef = std::unique_ptr<State>;

/// Stack-based state machine for managing game scenes.
///
/// Supports three operations:
/// - pushState:   Add a new state on top (optionally replacing the current one).
/// - popState:    Remove the top state and resume the one below.
/// - processStateChanges: Apply pending operations (called once per frame).
///
/// This deferred processing avoids modifying the stack mid-frame.
class StateMachine {
public:
    StateMachine() = default;
    ~StateMachine() = default;

    /// Schedule a new state to be pushed next frame.
    /// @param newState  The state to push.
    /// @param isReplacing If true, the current top state is removed first.
    void pushState(StateRef newState, bool isReplacing = true);

    /// Schedule the removal of the current top state.
    void popState();

    /// Apply any pending push/pop operations. Call once per frame before input.
    void processStateChanges();

    /// Get a reference to the currently active state.
    /// @pre The stack must not be empty.
    StateRef& getActiveState();

    /// Check whether the state stack is empty.
    [[nodiscard]] bool empty() const;

private:
    std::stack<StateRef> m_states;
    StateRef m_newState;

    bool m_isRemoving  = false;
    bool m_isAdding    = false;
    bool m_isReplacing = false;
};

} // namespace Engine
