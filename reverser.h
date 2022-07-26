#ifndef REVERSER_H
#define REVERSER_H
#include "enemy.h"

class Reverser : public Enemy {
  bool bonus;

 public:
  Reverser(Posn p);
  std::string attack(Character *target) override;
  int getAtk() override;
  int getDef() override;
  Item *getItem() override { return nullptr; };
};

#endif  // REVERSER_H
