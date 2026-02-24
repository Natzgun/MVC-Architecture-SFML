#include "Game/View/View.h"

View::View(Engine::GameDataRef data) : m_data(data) {
  // Ya no inicializa la ventana. Es administrada por el Engine.
}

void View::drawEsfera(int radio, int x, int y) {
  sf::CircleShape sphere(static_cast<float>(radio));
  sphere.setPosition(static_cast<float>(x), static_cast<float>(y));
  sphere.setFillColor(sf::Color::White);
  m_data->window->draw(sphere);
}

