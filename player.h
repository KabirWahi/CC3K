#ifndef PLAYER_H
#define PLAYER_H
#include "character.h"
#include "potion.h"

class Player : public Character {
 protected:
  int maxHP;
  bool barrier = false;
  char symbol = '@';

 public:
  bool knownPotions[6];
  virtual void addGold(int amount);
  virtual void addHealth(int amount);
  virtual void attack(Character *target);
  virtual bool hasBarrier() const override;
  virtual void toggleBarrier();
  virtual ~Player();
};

#endif  // PLAYER_H
