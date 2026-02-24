#ifndef REVOLUTION_GAME_VIEW_H
#define REVOLUTION_GAME_VIEW_H

#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Core/Game.hpp"
#include "IView.hpp"

class View : public Game::IView {
private:
  Engine::GameDataRef m_data;
public:
  explicit View(Engine::GameDataRef data);
  void drawEsfera(int radio, int x, int y) override;
};

#endif //REVOLUTION_GAME_VIEW_H