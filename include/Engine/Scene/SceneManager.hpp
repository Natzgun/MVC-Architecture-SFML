#pragma once

#include "Scene.hpp"
#include <memory>
#include <stack>

namespace Engine {

using SceneRef = std::unique_ptr<Scene>;

/// Stack-based scene manager for managing game scenes.
///
/// Supports three operations:
/// - pushScene:   Add a new scene on top (optionally replacing the current one).
/// - popScene:    Remove the top scene and resume the one below.
/// - processSceneChanges: Apply pending operations (called once per frame).
///
/// This deferred processing avoids modifying the stack mid-frame.
class SceneManager {
public:
    SceneManager() = default;
    ~SceneManager() = default;

    /// Schedule a new scene to be pushed next frame.
    /// @param newScene   The scene to push.
    /// @param isReplacing If true, the current top scene is removed first.
    void pushScene(SceneRef newScene, bool isReplacing = true);

    /// Schedule the removal of the current top scene.
    void popScene();

    /// Apply any pending push/pop operations. Call once per frame before input.
    void processSceneChanges();

    /// Get a reference to the currently active scene.
    /// @pre The stack must not be empty.
    [[nodiscard]] SceneRef& getActiveScene();

    /// Check whether the scene stack is empty.
    [[nodiscard]] bool empty() const;

private:
    std::stack<SceneRef> m_scenes;
    SceneRef m_newScene;

    bool m_isRemoving  = false;
    bool m_isAdding    = false;
    bool m_isReplacing = false;
};

} // namespace Engine
