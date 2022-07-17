#ifndef PHOENIX_H
#define PHOENIX_H
#include "enemy.h"

class Phoenix : public Enemy {
 public:
  Phoenix(Posn p);
  void attack(Character *target) override;
  int getAtk() override;
  int getDef() override;
};

#endif // PHOENIX_H