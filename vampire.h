#ifndef VAMPIRE_H
#define VAMPIRE_H
#include "enemy.h"

class Vampire : public Enemy {
 public:
  Vampire(Posn p);
  void attack(Character *target) override;
  int getAtk() override;
  int getDef() override;
  Item *getItem() override { return nullptr; };
};

#endif  // VAMPIRE_H