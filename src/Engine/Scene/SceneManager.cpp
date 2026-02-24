#include "Engine/Scene/SceneManager.hpp"

namespace Engine {

void SceneManager::pushScene(SceneRef newScene, bool isReplacing) {
    m_isAdding = true;
    m_isReplacing = isReplacing;
    m_newScene = std::move(newScene);
}

void SceneManager::popScene() {
    m_isRemoving = true;
}

void SceneManager::processSceneChanges() {
    // Handle removal request
    if (m_isRemoving && !m_scenes.empty()) {
        m_scenes.pop();
        if (!m_scenes.empty()) {
            m_scenes.top()->resume();
        }
        m_isRemoving = false;
    }

    // Handle addition request
    if (m_isAdding) {
        if (!m_scenes.empty()) {
            if (m_isReplacing) {
                m_scenes.pop();
            } else {
                m_scenes.top()->pause();
            }
        }

        m_scenes.push(std::move(m_newScene));
        m_scenes.top()->init();
        m_isAdding = false;
    }
}

SceneRef& SceneManager::getActiveScene() {
    return m_scenes.top();
}

bool SceneManager::empty() const {
    return m_scenes.empty();
}

} // namespace Engine
