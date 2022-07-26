#include "troll.h"

#include <iostream>

using namespace std;

Troll::Troll(Posn p, bool bonus): bonus{bonus} {
  atk = 25;
  def = 15;
  HP = 120;
  gold = 1;
  position = p;
  symbol = 'T';
  race = "Troll";
}

string Troll::attack(Character *target) {
  int hit = randomNum(2);
  string msg = "";
  if (hit == 1) {
    int damage = ceil(double(100) / double(100 + target->getDef()) * atk);
    if (target->hasBarrier()) {
      damage = ceil(double(damage) / double(2));
    }
    target->setHP(target->getHP() - damage);
    msg = msg + symbol + " deals " + to_string(damage) + " damage to PC. ";
    if (bonus) {
      hit = randomNum(4);
      if (hit == 1) {
        damage = ceil(double(100) / double(100 + target->getDef()) * atk);
        if (target->hasBarrier()) {
          damage = ceil(double(damage) / double(2));
        }
        target->setHP(target->getHP() - damage);
        msg = msg + symbol + " dealt another hit for " + to_string(damage) + " damage to PC. ";
      }
    }
  } else {
    msg = msg + symbol + " missed. ";
  }
  return msg;
}

int Troll::getAtk() { return atk; }

int Troll::getDef() { return def; }
