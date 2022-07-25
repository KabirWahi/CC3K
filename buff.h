#ifndef BUFF_H
#define BUFF_H
#include <string>

#include "player.h"

class Buff : public Player {
 protected:
  Player* player;
  int value;
  std::string name;

 public:
  Buff(Player* player);
  virtual ~Buff();
  int getAtk() override;
  int getDef() override;
  std::string attack(Character* target) override;
  void addGold(int amount) override;
  void addHealth(int amount) override;
  bool hasBarrier() const override;
  void toggleBarrier() override;
  int getHP() override;                                 // return HP
  int getGold() override;                               // return gold
  Posn getPosition() override;                          // return position
  char getSymbol() override;                            // return symbol
  std::string getRace() override;                       // return race
  void setPosition(Posn position) override;             // set position
  void setHP(int HP) override;                          // set HP
  void setGold(int gold) override;                      // set gold
  void setAtk(int atk) override;                        // set atk
  void setDef(int def) override;                        // set def
};

#endif
