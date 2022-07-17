#ifndef PHOENIX_H
#define PHOENIX_H
#include "enemy.h"

class Phoenix : public Enemy {
 public:
  Phoenix(Posn p);
  void attack(Character *target) override;
  int getAtk() override;
  int getDef() override;
  bool hasBarrier() const override { return false; };
};

#endif  // PHOENIX_H