#ifndef PLAYER_H
#define PLAYER_H
#include "character.h"
#include "potion.h"

class Player : public Character {
 protected:
  int maxHP;
  bool barrier = false;
  char symbol = '@';
  bool knownPotions[6] = {false, false, false, false, false, false};

 public:
  virtual void toggleknownPotions(int index);
  virtual bool getknownPotions(int index);
  virtual void addGold(int amount);
  virtual void addHealth(int amount);
  virtual void attack(Character *target);
  virtual bool hasBarrier() const override;
  virtual void toggleBarrier();
  virtual ~Player();
};

#endif  // PLAYER_H
