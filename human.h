#ifndef HUMAN_H
#define HUMAN_H
#include "player.h"

class Human : public Player {
 protected:
  int maxHP = 140;
 public:
  Human(Posn p);
};

#endif  // HUMAN_H