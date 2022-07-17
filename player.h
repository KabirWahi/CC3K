#ifndef PLAYER_H
#define PLAYER_H
#include "character.h"

class Player : public Character {
 protected:
  int maxHP;
  bool barrier = false;
  char symbol = '@';

 public:
  virtual int getAtk() = 0;
  virtual int getDef() = 0;
  virtual void attack(Character *target) = 0;
  virtual bool hasBarrier() const;
  void toggleBarrier();
};

#endif  // PLAYER_H
