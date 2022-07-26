#ifndef TROLL_H
#define TROLL_H
#include "enemy.h"

class Troll : public Enemy {
  bool bonus;

 public:
  Troll(Posn p, bool bonus);
  std::string attack(Character *target) override;
  int getAtk() override;
  int getDef() override;
  Item *getItem() override { return nullptr; };
};

#endif  // TROLL_H
