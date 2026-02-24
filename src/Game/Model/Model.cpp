#include "Game/Model/Model.h"
#include <iostream>

Model::Model() {
  this->pos_x = 0;
  this->pos_y = 0;
  this->w = false;
  this->a = false;
  this->s = false;
  this->d = false;
  this->cont_w = 0;
  this->cont_a = 0;
  this->cont_s = 0;
  this->cont_d = 0;
}

void Model::listen_W(bool _w) {
  w = _w;
  if (w) {
    cont_w ++;
    std::cout << "Tecla W presionada: " << this->cont_w << std::endl;
  }
}

void Model::listen_A(bool _a) {
  a = _a;
  if (a) {
    cont_a ++;
    std::cout << "Tecla A presionada: " << this->cont_a << std::endl;
  }
}

void Model::listen_S(bool _s) {
  s = _s;
  if (s) {
    cont_s ++;
    std::cout << "Tecla S presionada: " << this->cont_s << std::endl;
  }
}

void Model::listen_D(bool _d) {
  d = _d;
  if (d) {
    cont_d ++;
    std::cout << "Tecla D presionada: " << this->cont_d << std::endl;
  }
}

void Model::reset() {
  this->w = false;
  this->a = false;
  this->s = false;
  this->d = false;
}

void Model::update() {
  if (w) pos_y -= 5;
  if (a) pos_x -= 5;
  if (s) pos_y += 5;
  if (d) pos_x += 5;
}

Model::~Model() {

}

int Model::getPosX() {
  return this->pos_x;
}

int Model::getPosY() {
  return this->pos_y;
}

void Model::setPosX(int x) {
  pos_x = x;
}

void Model::setPosY(int y) {
  pos_y = y;
}

