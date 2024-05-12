//
// Created by natzgun on 1/08/23.
//

#ifndef REVOLUTION_GAME_MODEL_H
#define REVOLUTION_GAME_MODEL_H


class Model {
private:
  int pos_x, pos_y;
  bool w,a,s,d;
  long cont_w, cont_a, cont_s, cont_d;
public:
  Model();
  int& getPosX();
  int& getPosY();
  void setPosX(int);
  void setPosY(int);

  void listen_W(bool);
  void listen_A(bool);
  void listen_S(bool);
  void listen_D(bool);
  void reset();
  ~Model();
};

#endif //REVOLUTION_GAME_MODEL_H
