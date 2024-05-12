#include "View.h"

View::View() {
  int fps = 60;
  window.create(sf::VideoMode(1280, 720), "Examen MVC");
  window.setFramerateLimit(fps);
}


void View::drawEsfera(int radio, int x, int y) {
  sf::CircleShape sphere(50.f);
  sphere.move(x,y);
  sphere.setFillColor(sf::Color::White);
  window.draw(sphere);
}

sf::Event& View::getEvent() {
  return evento;
}

bool View::getVentanaPollEvent() {
  return window.pollEvent(getEvent());
}

void View::getCloseWindow() {
  window.close();
}

bool View::getKeyboard_W() {
  return sf::Keyboard::isKeyPressed(sf::Keyboard::W);
}

bool View::getKeyboard_A() {
  return sf::Keyboard::isKeyPressed(sf::Keyboard::A);
}

bool View::getKeyboard_S() {
  return sf::Keyboard::isKeyPressed(sf::Keyboard::S);
}

bool View::getKeyboard_D() {
  return sf::Keyboard::isKeyPressed(sf::Keyboard::D);
}

sf::RenderWindow& View::getWindowMain() {
  return window;
}

