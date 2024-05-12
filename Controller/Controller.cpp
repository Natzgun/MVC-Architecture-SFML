#include "Controller.h"

Controller::Controller() {
  vista = new View();
  modelo = new Model();
}

void Controller::ejecutar() {
  int y = modelo->getPosY();
  int x = modelo->getPosX();
  while (vista->getWindowMain().isOpen()) {
    vista->getWindowMain().clear();
    while (vista->getVentanaPollEvent()) {
      switch (vista->getEvent().type) {
        // El 0 = Closed
        case 0:
          vista->getCloseWindow();
          break;
      }
    }
    if (vista->getKeyboard_W()) {
      y -= 5;
      modelo->setPosY(y);
      vista->drawEsfera(50, x , y);
      modelo->listen_W(true);
    }
    if (vista->getKeyboard_A()) {
      x -= 5;
      modelo->setPosX(x);
      vista->drawEsfera(50, x, y);
      modelo->listen_A(true);
    }
    if (vista->getKeyboard_S()) {
      y += 5;
      modelo->setPosY(y);
      vista->drawEsfera(50, x, y);
      modelo->listen_S(true);
    }
    if (vista->getKeyboard_D()) {
      x += 5;
      modelo->setPosX(x);
      vista->drawEsfera(50, x, y);
      modelo->listen_D(true);
    }

    vista->drawEsfera(50, x, y);
    vista->getWindowMain().display();
    modelo->reset();
  }
}

Controller::~Controller() {
  delete vista;
  delete modelo;
}
