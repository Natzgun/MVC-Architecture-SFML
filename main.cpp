// Archivo main.cpp
#include <SFML/Graphics.hpp>
#include "Model/Model.h"
#include "View/View.h"
#include "Controller/Controller.h"

int main() {
  sf::RenderWindow window(sf::VideoMode(800, 600), "Mi Aplicación SFML");
  // Como ejemplo crea un circulo
  sf::CircleShape shape(100.f);
  shape.setFillColor(sf::Color::Green);

  Model modelo; // Instancia del modelo
  View vista(window); // Instancia de la vista, pasando la ventana como parámetro
  Controller controlador(modelo, vista); // Instancia del controlador, pasando el modelo y la vista como parámetros

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        // window.close(); // Es un ejemmplo pero esto lo deberia manerar el controller
        controlador.procesarEvento(event); // El controlador maneja los eventos y actualiza el modelo y la vista en consecuencia
      }
    }
    /* Este es un ejemplo
    window.clear();
    window.draw(shape);
    window.display();
    */
    controlador.actualizar(); // El controlador actualiza el modelo y la vista en cada iteración
    vista.dibujar(); // La vista dibuja los elementos en la ventana
  }

  return 0;
}
