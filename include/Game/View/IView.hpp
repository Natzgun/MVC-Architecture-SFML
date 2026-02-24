#ifndef REVOLUTION_GAME_IVIEW_HPP
#define REVOLUTION_GAME_IVIEW_HPP

namespace Game {
    // Interface Segregation & Dependency Inversion:
    // El controlador solo necesita saber que algo puede dibujar una esfera,
    // no necesita saber que es una ventana de SFML.
    class IView {
    public:
        virtual ~IView() = default;
        virtual void drawEsfera(int radio, int x, int y) = 0;
    };
}

#endif //REVOLUTION_GAME_IVIEW_HPP