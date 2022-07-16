#ifndef ENEMY_H
#define ENEMY_H
#include "character.h"

class Enemy {
 public:
  bool compass = false;
  char getSymbol();
};

#endif  // ENEMY_H
