#ifndef REVOLUTION_GAME_GAME_HPP
#define REVOLUTION_GAME_GAME_HPP

#include <SFML/Graphics.hpp>
#include "States/StateMachine.hpp"
#include "Core/ResourceManager.hpp"
#include <memory>
#include <string>

namespace Engine {

    // Estructura de Contexto: Contiene los sistemas principales
    // Cada estado recibe un puntero a este contexto para poder acceder a la ventana, texturas, etc.
    struct GameData {
        std::unique_ptr<StateMachine> machine;
        std::unique_ptr<sf::RenderWindow> window;
        TextureManager textures;
        FontManager fonts;
        SoundBufferManager sounds;
    };

    using GameDataRef = std::shared_ptr<GameData>;

    class Game {
    public:
        Game(int width, int height, const std::string& title);
        ~Game() = default;

        // Inicia el ciclo principal del juego
        void run();

        // Obtener el contexto de los datos compartidos
        GameDataRef getContext() const { return m_data; }

    private:
        const float dt = 1.0f / 60.0f; // Delta Time fijo (60 fps)
        sf::Clock m_clock;
        GameDataRef m_data = std::make_shared<GameData>();
    };
}

#endif //REVOLUTION_GAME_GAME_HPP