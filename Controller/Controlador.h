//
// Created by natzgun on 10/06/23.
//

#ifndef MVC_ARCHITECTURE_SFML_CONTROLADOR_H
#define MVC_ARCHITECTURE_SFML_CONTROLADOR_H

// Archivo Controlador.h
#pragma once
#include <SFML/Window/Event.hpp>
#include "../Model/Modelo.h"
#include "../View/Vista.h"

class Controlador {
private:
  Modelo& modelo; // Referencia al modelo
  Vista& vista; // Referencia a la vista

public:
  Controlador(Modelo& modelo, Vista& vista);

  void procesarEvento(const sf::Event& evento); // Método para procesar eventos de SFML

  void actualizar(); // Método para actualizar el modelo y la vista en cada iteración

  // Otros métodos y funciones relacionados con la interacción y el control
};


#endif //MVC_ARCHITECTURE_SFML_CONTROLADOR_H
