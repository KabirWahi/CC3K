#ifndef MERCHANT_H
#define MERCHANT_H
#include "enemy.h"

class Merchant : public Enemy {
 public:
  Merchant(Posn p);
  void attack(Character *target) override;
  int getAtk() override;
  int getDef() override;
};

#endif // MERCHANT_H