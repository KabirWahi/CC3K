#ifndef TROLL_H
#define TROLL_H
#include "enemy.h"

class Troll : public Enemy {
 public:
  Troll(Posn p);
  void attack(Character *target) override;
  int getAtk() override;
  int getDef() override;
  bool hasBarrier() const override { return false; };
  Item *getItem() override { return nullptr; };
};

#endif  // TROLL_H