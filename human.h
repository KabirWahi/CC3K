#ifndef HUMAN_H
#define HUMAN_H
#include "player.h"

class Human : public Player {
 protected:
  int maxHP = 140;

 public:
  Human(Posn p);
  void attack(Character *target) override;
  int getAtk() override;
  int getDef() override;
};

#endif  // HUMAN_H