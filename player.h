#ifndef PLAYER_H
#define PLAYER_H
#include "character.h"

class Player : public Character {
 protected:
  int maxHP;
  bool barrier = false;

 public:
  virtual Player *init(int row, int col) = 0;
  virtual int getAtk() = 0;
  virtual int getDef() = 0;
  virtual void attack(Character *target) = 0;
  void toggleBarrier();
};

#endif  // PLAYER_H