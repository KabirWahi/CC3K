#ifndef TROLL_H
#define TROLL_H
#include "enemy.h"

class Troll : public Enemy {
 public:
  Troll(Posn p);
  int getAtk() override;
  int getDef() override;
  Item *getItem() override { return nullptr; };
};

#endif  // TROLL_H