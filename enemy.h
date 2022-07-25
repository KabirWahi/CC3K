#ifndef ENEMY_H
#define ENEMY_H
#include "character.h"
#include "item.h"

class Enemy : public Character {
 public:
  bool compass = false;
  virtual std::string attack(Character *target);
  virtual int getAtk() = 0;
  virtual int getDef() = 0;
  virtual Item * getItem() = 0;
  bool hasBarrier() const override { return false; };
  virtual bool isHostile() { return true; };
  virtual void setHostile() {};
  virtual ~Enemy() {};
};

#endif  // ENEMY_H
