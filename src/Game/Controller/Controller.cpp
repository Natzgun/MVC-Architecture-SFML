#include "Game/Controller/Controller.h"

Controller::Controller(Engine::GameDataRef data) {
  vista = std::make_unique<View>(data);
  modelo = std::make_unique<Model>();
}

void Controller::procesarEntrada() {
  modelo->listen_W(sf::Keyboard::isKeyPressed(sf::Keyboard::W));
  modelo->listen_A(sf::Keyboard::isKeyPressed(sf::Keyboard::A));
  modelo->listen_S(sf::Keyboard::isKeyPressed(sf::Keyboard::S));
  modelo->listen_D(sf::Keyboard::isKeyPressed(sf::Keyboard::D));
}

void Controller::actualizar() {
  modelo->update();
}

void Controller::dibujar() {
  vista->drawEsfera(50, modelo->getPosX(), modelo->getPosY());
}
