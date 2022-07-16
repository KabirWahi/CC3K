#include "enemy.h"

class Vampire : public Enemy {
 public:
  Vampire(Posn p);
  void attack(Character *target) override;
  int getAtk() override;
  int getDef() override;
};