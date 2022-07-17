#ifndef DRAGON_H
#define DRAGON_H
#include "enemy.h"

class Dragon : public Enemy {
 public:
  Dragon(Posn p);
  void attack(Character *target) override;
  int getAtk() override;
  int getDef() override;
};

#endif // DRAGON_H