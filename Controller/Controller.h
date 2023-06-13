//
// Created by natzgun on 10/06/23.
//

#ifndef MVC_ARCHITECTURE_SFML_CONTROLLER_H
#define MVC_ARCHITECTURE_SFML_CONTROLLER_H

// Archivo Controller.h
#pragma once
#include <SFML/Window/Event.hpp>
#include "../Model/Model.h"
#include "../View/View.h"

class Controller {
private:
  Model& modelo; // Referencia al modelo
  View& vista; // Referencia a la vista

public:
  Controller(Model& modelo, View& vista);

  void procesarEvento(const sf::Event& evento); // Método para procesar eventos de SFML

  void actualizar(); // Método para actualizar el modelo y la vista en cada iteración

  // Otros métodos y funciones relacionados con la interacción y el control
};


#endif //MVC_ARCHITECTURE_SFML_CONTROLLER_H
