//
// Created by natzgun on 10/06/23.
//

#ifndef MVC_ARCHITECTURE_SFML_VIEW_H
#define MVC_ARCHITECTURE_SFML_VIEW_H

// Archivo View.h
#pragma once
#include <SFML/Graphics.hpp>

class View {
private:
  sf::RenderWindow& ventana; // Referencia a la ventana de SFML
  // Otros atributos y datos de la vista

public:
  View(sf::RenderWindow& ventana);

  void dibujar(); // Método para dibujar elementos en la ventana

  // Otros métodos y funciones relacionados con la representación visual
};


#endif //MVC_ARCHITECTURE_SFML_VIEW_H
