//
// Created by natzgun on 1/08/23.
//

#ifndef REVOLUTION_GAME_CONTROLLER_H
#define REVOLUTION_GAME_CONTROLLER_H


#include "../View/View.h"
#include "../Model/Model.h"
#include <memory>

class Controller {
private:
  std::unique_ptr<View> vista;
  std::unique_ptr<Model> modelo;

  void procesarEntrada();
  void actualizar();
  void dibujar();
public:
  Controller();
  void ejecutar();
  ~Controller();
};


#endif //REVOLUTION_GAME_CONTROLLER_H
