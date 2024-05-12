//
// Created by natzgun on 1/08/23.
//

#ifndef REVOLUTION_GAME_CONTROLLER_H
#define REVOLUTION_GAME_CONTROLLER_H


#include "../View/View.h"
#include "../Model/Model.h"

class Controller {
private:
  View* vista;
  Model* modelo;
public:
  Controller();
  void ejecutar();
  ~Controller();
};


#endif //REVOLUTION_GAME_CONTROLLER_H
