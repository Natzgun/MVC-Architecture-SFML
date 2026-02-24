#ifndef REVOLUTION_GAME_VIEW_H
#define REVOLUTION_GAME_VIEW_H

#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Core/Game.hpp"

class View {
private:
  Engine::GameDataRef m_data;
public:
  explicit View(Engine::GameDataRef data);
  void drawEsfera(int,int,int);
};

#endif //REVOLUTION_GAME_VIEW_H
