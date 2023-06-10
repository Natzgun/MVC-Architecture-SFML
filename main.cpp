// Archivo main.cpp
#include <SFML/Graphics.hpp>
#include "Model/Modelo.h"
#include "View/Vista.h"
#include "Controller/Controlador.h"

int main() {
  sf::RenderWindow window(sf::VideoMode(800, 600), "Mi Aplicación SFML");

  Modelo modelo; // Instancia del modelo
  Vista vista(window); // Instancia de la vista, pasando la ventana como parámetro
  Controlador controlador(modelo, vista); // Instancia del controlador, pasando el modelo y la vista como parámetros

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      controlador.procesarEvento(event); // El controlador maneja los eventos y actualiza el modelo y la vista en consecuencia
    }

    controlador.actualizar(); // El controlador actualiza el modelo y la vista en cada iteración
    vista.dibujar(); // La vista dibuja los elementos en la ventana
  }

  return 0;
}
