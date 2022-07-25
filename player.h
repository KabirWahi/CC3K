#ifndef PLAYER_H
#define PLAYER_H
#include "character.h"
#include "item.h"

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
  virtual std::string attack(Character *target) override;
  virtual bool hasBarrier() const override;
  std::string usePotion(Item* item);
  virtual void toggleBarrier();
  virtual ~Player();
};

#endif  // PLAYER_H
