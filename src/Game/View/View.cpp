#include "Game/View/View.h"

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

sf::RenderWindow& View::getWindowMain() {
  return window;
}

