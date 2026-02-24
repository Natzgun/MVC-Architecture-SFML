#include "Engine/Core/Application.hpp"

namespace Engine {

Application::Application(unsigned int width, unsigned int height, const std::string& title)
    : m_renderer(width, height, title)
    , m_context{m_renderer, m_input, m_audio, m_scenes, m_events, {}, {}, {}}
{
    m_renderer.setFramerateLimit(60);
}

void Application::run() {
    float currentTime = m_clock.getElapsedTime().asSeconds();
    float accumulator = 0.0f;

    while (m_renderer.isOpen() && !m_scenes.empty()) {
        // 1. Apply pending scene changes (e.g., menu -> gameplay)
        m_scenes.processSceneChanges();

        // If all scenes were popped during processing, exit
        if (m_scenes.empty()) break;

        // Fixed timestep accumulation
        float newTime = m_clock.getElapsedTime().asSeconds();
        float frameTime = newTime - currentTime;

        // Clamp to avoid spiral of death
        if (frameTime > 0.25f)
            frameTime = 0.25f;

        currentTime = newTime;
        accumulator += frameTime;

        // 2. Poll window events through InputManager
        m_input.pollEvents(m_renderer);

        // Handle window close request
        if (m_input.isWindowCloseRequested()) {
            m_renderer.close();
            continue;
        }

        // 3. Handle scene input
        m_scenes.getActiveScene()->handleInput(dt);

        // 4. Fixed-rate logic updates
        while (accumulator >= dt) {
            m_scenes.getActiveScene()->update(dt);
            accumulator -= dt;
        }

        // 5. Render with interpolation
        float interpolation = accumulator / dt;
        m_renderer.clear();
        m_scenes.getActiveScene()->draw(interpolation);
        m_renderer.display();
    }
}

Context& Application::context() {
    return m_context;
}

const Context& Application::context() const {
    return m_context;
}

} // namespace Engine
