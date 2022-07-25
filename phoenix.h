#ifndef PHOENIX_H
#define PHOENIX_H
#include "enemy.h"

class Phoenix : public Enemy {
 public:
  Phoenix(Posn p);
  int getAtk() override;
  int getDef() override;
  Item *getItem() override { return nullptr; };
};

#endif  // PHOENIX_H