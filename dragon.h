#ifndef DRAGON_H
#define DRAGON_H
#include "enemy.h"

class Dragon : public Enemy {
 public:
  Dragon(Posn p);
  void attack(Character *target) override;
  int getAtk() override;
  int getDef() override;
  bool hasBarrier() const override { return false; };
};

#endif  // DRAGON_H