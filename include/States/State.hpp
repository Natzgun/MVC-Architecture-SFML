#ifndef REVOLUTION_GAME_STATE_HPP
#define REVOLUTION_GAME_STATE_HPP

namespace Engine {
    // Interfaz base para cualquier pantalla o escena del juego.
    class State {
    public:
        virtual ~State() = default;

        // Se llama al inicializar el estado (cargar recursos iniciales)
        virtual void init() = 0;

        // Gestión de la entrada de usuario
        virtual void handleInput() = 0;

        // Lógica de juego por frame (dt = delta time en segundos)
        virtual void update(float dt) = 0;

        // Renderizado del frame (dt opcional para interpolaciones)
        virtual void draw(float dt) = 0;

        // Si el estado es pausado (ej. abrimos un menú superpuesto)
        virtual void pause() {}
        virtual void resume() {}
    };
}

#endif //REVOLUTION_GAME_STATE_HPP