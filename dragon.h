#ifndef DRAGON_H
#define DRAGON_H
#include "enemy.h"
#include "item.h"

class Dragon : public Enemy {
  protected:
   Item *guarding;
 public:
  Dragon(Posn p, Item *i);
  std::string attack(Character *target) override;
  int getAtk() override;
  int getDef() override;
  Item * getItem() override;
};

#endif  // DRAGON_H
