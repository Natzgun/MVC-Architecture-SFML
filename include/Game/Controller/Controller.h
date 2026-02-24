//
// Created by natzgun on 1/08/23.
//

#ifndef REVOLUTION_GAME_CONTROLLER_H
#define REVOLUTION_GAME_CONTROLLER_H

#include "Game/View/IView.hpp"
#include "Game/Model/Model.h"
#include "Core/Game.hpp"
#include <memory>

class Controller {
private:
  // Dependemos de la interfaz IView, no de la clase View concreta (DIP)
  Game::IView* vista;
  Model* modelo;

public:
  // Inyección de dependencias por constructor
  Controller(Model* m, Game::IView* v);

  void procesarEntrada();
  void actualizar();
  void dibujar();

  ~Controller() = default;
};

#endif //REVOLUTION_GAME_CONTROLLER_H
