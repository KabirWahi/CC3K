#ifndef MERCHANT_H
#define MERCHANT_H
#include "enemy.h"

class Merchant : public Enemy {
 protected:
  static bool hostile;

 public:
  Merchant(Posn p);
  bool isHostile() override;
  void setHostile() override;
  std::string attack(Character *target) override;
  int getAtk() override;
  int getDef() override;
  void setHP(int HP) override;
  Item *getItem() override { return nullptr; };
};

#endif  // MERCHANT_H