#include "Controller.h"

Controller::Controller() {
  vista = new View();
  modelo = new Model();
}

void Controller::ejecutar() {
  while (vista->getWindowMain().isOpen()) {
    procesarEntrada();
    actualizar();
    dibujar();
  }
}

void Controller::procesarEntrada() {
  while (vista->getVentanaPollEvent()) {
    if (vista->getEvent().type == sf::Event::Closed) {
      vista->getCloseWindow();
    }
  }

  modelo->listen_W(vista->getKeyboard_W());
  modelo->listen_A(vista->getKeyboard_A());
  modelo->listen_S(vista->getKeyboard_S());
  modelo->listen_D(vista->getKeyboard_D());
}

void Controller::actualizar() {
  int y = modelo->getPosY();
  int x = modelo->getPosX();

  if (vista->getKeyboard_W()) y -= 5;
  if (vista->getKeyboard_A()) x -= 5;
  if (vista->getKeyboard_S()) y += 5;
  if (vista->getKeyboard_D()) x += 5;

  modelo->setPosX(x);
  modelo->setPosY(y);
}

void Controller::dibujar() {
  vista->getWindowMain().clear();
  vista->drawEsfera(50, modelo->getPosX(), modelo->getPosY());
  vista->getWindowMain().display();
}

Controller::~Controller() {
  delete vista;
  delete modelo;
}
