#ifndef ENEMY_H
#define ENEMY_H
#include "character.h"
#include "item.h"

class Enemy : public Character {
 public:
  bool compass = false;
  virtual void attack(Character *target) = 0;
  virtual int getAtk() = 0;
  virtual int getDef() = 0;
  virtual Item * getItem() = 0;
};

#endif  // ENEMY_H
