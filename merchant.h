#ifndef MERCHANT_H
#define MERCHANT_H
#include "enemy.h"

class Merchant : public Enemy {
 protected:
  static bool hostile;

 public:
  Merchant(Posn p);
  void attack(Character *target) override;
  int getAtk() override;
  int getDef() override;
  Item *getItem() override { return nullptr; };
};

#endif  // MERCHANT_H