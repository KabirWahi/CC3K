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
  ~Buff() override;
  int getAtk() = 0;
  int getDef() = 0;
  void attack(Character* target);
  void addGold(int amount) override;
  void addHealth(int amount) override;
  bool hasBarrier() = 0;
  void toggleBarrier() = 0;
  int getHP() = 0;                                 // return HP
  int getGold() = 0;                               // return gold
  Posn getPosition() = 0;                          // return position
  char getSymbol() = 0;                            // return symbol
  std::string getRace() = 0;                       // return race
  void setPosition(Posn position) = 0;             // set position
  void setHP(int HP) = 0;                          // set HP
  void setGold(int gold) = 0;                      // set gold
  void setAtk(int atk) = 0;                        // set atk
  void setDef(int def) = 0;                        // set def
};

#endif
