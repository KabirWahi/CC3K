#ifndef CHARACTER_H
#define CHARACTER_H
#include <math.h>

#include <string>

#include "posn.h"

class Character {
 protected:
  int HP;
  int atk;
  int def;
  int gold;
  char symbol;
  std::string race;
  Posn position;
  int whichChamber;

 public:
  ~Character();                                // destructor
  virtual int getAtk();                        // return atk
  virtual int getDef();                        // return def
  virtual int getHP();                         // return HP
  virtual int getGold();                       // return gold
  virtual Posn getPosition();                  // return position
  virtual char getSymbol();                    // return symbol
  virtual std::string getRace();               // return race
  virtual void setPosition(Posn position);     // set position
  virtual void attack(Character *target) = 0;  // attack target
  virtual void setHP(int HP);                  // set HP
  virtual void setGold(int gold);              // set gold
  virtual void setAtk(int atk);                // set atk
  virtual void setDef(int def);                // set def
  virtual bool hasBarrier() const = 0;         // return barrier
};

#endif  // CHARACTER_H
