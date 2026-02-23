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
  modelo->update();
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
