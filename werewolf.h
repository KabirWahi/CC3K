#ifndef WERE_WOLF_H
#define WERE_WOLF_H
#include "enemy.h"

class Werewolf : public Enemy {
 public:
  Werewolf(Posn p);
  void attack(Character *target) override;
  int getAtk() override;
  int getDef() override;
};

#endif // WERE_WOLF_H