//
// Created by natzgun on 1/08/23.
//

#ifndef REVOLUTION_GAME_CONTROLLER_H
#define REVOLUTION_GAME_CONTROLLER_H

#include "Game/View/View.h"
#include "Game/Model/Model.h"
#include "Core/Game.hpp"
#include <memory>

class Controller {
private:
  std::unique_ptr<View> vista;
  std::unique_ptr<Model> modelo;

public:
  explicit Controller(Engine::GameDataRef data);

  // Expuestos temporalmente para que el GameState pueda llamarlos.
  void procesarEntrada();
  void actualizar();
  void dibujar();

  ~Controller() = default;
};

#endif //REVOLUTION_GAME_CONTROLLER_H
