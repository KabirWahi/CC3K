#ifndef GOBLIN_H
#define GOBLIN_H
#include "enemy.h"

class Goblin : public Enemy {
  bool bonus;
 public:
  Goblin(Posn p, bool bonus);
  std::string attack(Character *target) override;
  int getAtk() override;
  int getDef() override;
  Item *getItem() override { return nullptr; };
};

#endif  // GOBLIN_H
