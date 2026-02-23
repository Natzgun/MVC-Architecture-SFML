#ifndef REVOLUTION_GAME_VIEW_H
#define REVOLUTION_GAME_VIEW_H

// Archivo View.h
#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

  class View {
  private:
    sf::RenderWindow window;
    sf::Event evento;
    int fps;
  public:
    View();
    sf::Event& getEvent();
    bool getVentanaPollEvent();
    void getCloseWindow();
    void drawEsfera(int,int,int);

    sf::RenderWindow& getWindowMain();

  };

#endif //REVOLUTION_GAME_VIEW_H
