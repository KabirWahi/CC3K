#ifndef TROLL_H
#define TROLL_H
#include "enemy.h"

class Troll : public Enemy {
 public:
  Troll(Posn p);
  void attack(Character *target) override;
  int getAtk() override;
  int getDef() override;
};

#endif // TROLL_H