#ifndef GOBLIN_H
#define GOBLIN_H
#include "enemy.h"

class Goblin : public Enemy {
 public:
  Goblin(Posn p);
  void attack(Character *target) override;
  int getAtk() override;
  int getDef() override;
};

#endif // GOBLIN_H
