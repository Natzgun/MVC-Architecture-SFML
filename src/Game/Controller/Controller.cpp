#include "Game/Controller/Controller.h"

Controller::Controller() {
  vista = std::make_unique<View>();
  modelo = std::make_unique<Model>();
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

  modelo->listen_W(sf::Keyboard::isKeyPressed(sf::Keyboard::W));
  modelo->listen_A(sf::Keyboard::isKeyPressed(sf::Keyboard::A));
  modelo->listen_S(sf::Keyboard::isKeyPressed(sf::Keyboard::S));
  modelo->listen_D(sf::Keyboard::isKeyPressed(sf::Keyboard::D));
}

void Controller::actualizar() {
  modelo->update();
}

void Controller::dibujar() {
  vista->getWindowMain().clear();
  vista->drawEsfera(50, modelo->getPosX(), modelo->getPosY());
  vista->getWindowMain().display();
}

Controller::~Controller() = default;
