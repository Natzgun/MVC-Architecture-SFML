#pragma once

#include <functional>
#include <unordered_map>
#include <vector>
#include <typeindex>
#include <memory>
#include <algorithm>

namespace Engine {

/// Unique handle returned when subscribing to an event.
/// Use it to unsubscribe later.
using SubscriptionID = std::size_t;

/// Type-erased base for event handler wrappers.
struct IEventHandler {
    virtual ~IEventHandler() = default;
    SubscriptionID id = 0;
};

/// Typed event handler that stores the callback for a specific event type.
template <typename EventType>
struct EventHandler : IEventHandler {
    std::function<void(const EventType&)> callback;

    explicit EventHandler(std::function<void(const EventType&)> cb)
        : callback(std::move(cb)) {}
};

/// Observer-pattern event bus for decoupled inter-module communication.
///
/// Modules publish events without knowing who listens, and subscribers
/// react without knowing who published. This eliminates tight coupling
/// between engine subsystems and game code.
///
/// Usage:
/// @code
///   struct PlayerDied { int playerID; };
///
///   EventBus bus;
///   auto id = bus.subscribe<PlayerDied>([](const PlayerDied& e) {
///       // handle event
///   });
///
///   bus.publish(PlayerDied{1});
///   bus.unsubscribe<PlayerDied>(id);
/// @endcode
///
/// Thread safety: NOT thread-safe. All calls must happen on the same thread.
class EventBus {
public:
    EventBus() = default;
    ~EventBus() = default;

    // Non-copyable, movable
    EventBus(const EventBus&) = delete;
    EventBus& operator=(const EventBus&) = delete;
    EventBus(EventBus&&) = default;
    EventBus& operator=(EventBus&&) = default;

    /// Subscribe to an event type with a callback.
    /// @tparam EventType The event struct to listen for.
    /// @param callback   Function to invoke when the event is published.
    /// @return A SubscriptionID that can be used to unsubscribe.
    template <typename EventType>
    SubscriptionID subscribe(std::function<void(const EventType&)> callback) {
        auto handler = std::make_unique<EventHandler<EventType>>(std::move(callback));
        handler->id = m_nextID++;

        SubscriptionID id = handler->id;
        auto& handlers = m_handlers[std::type_index(typeid(EventType))];
        handlers.push_back(std::move(handler));
        return id;
    }

    /// Unsubscribe a previously registered handler.
    /// @tparam EventType The event type the handler was registered for.
    /// @param id         The SubscriptionID returned by subscribe().
    template <typename EventType>
    void unsubscribe(SubscriptionID id) {
        auto key = std::type_index(typeid(EventType));
        auto it = m_handlers.find(key);
        if (it == m_handlers.end()) return;

        auto& handlers = it->second;
        handlers.erase(
            std::remove_if(handlers.begin(), handlers.end(),
                [id](const std::unique_ptr<IEventHandler>& h) {
                    return h->id == id;
                }),
            handlers.end());
    }

    /// Publish an event, invoking all registered handlers for that type.
    /// @tparam EventType The event struct being published.
    /// @param event      The event instance to broadcast.
    template <typename EventType>
    void publish(const EventType& event) {
        auto key = std::type_index(typeid(EventType));
        auto it = m_handlers.find(key);
        if (it == m_handlers.end()) return;

        for (const auto& baseHandler : it->second) {
            auto* typedHandler = static_cast<EventHandler<EventType>*>(baseHandler.get());
            typedHandler->callback(event);
        }
    }

    /// Remove all handlers for all event types.
    void clear() {
        m_handlers.clear();
    }

private:
    std::unordered_map<std::type_index, std::vector<std::unique_ptr<IEventHandler>>> m_handlers;
    SubscriptionID m_nextID = 1;
};

} // namespace Engine
