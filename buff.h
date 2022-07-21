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
  bool hasBarrier();
  void toggleBarrier();
  int getHP();                                 // return HP
  int getGold();                               // return gold
  Posn getPosition();                          // return position
  char getSymbol();                            // return symbol
  std::string getRace();                       // return race
  void setPosition(Posn position);             // set position
  void setHP(int HP);                          // set HP
  void setGold(int gold);                      // set gold
  void setAtk(int atk);                        // set atk
  void setDef(int def);                        // set def
};

#endif
