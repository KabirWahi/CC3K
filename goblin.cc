#include "goblin.h"

#include <iostream>

using namespace std;

Goblin::Goblin(Posn p, bool bonus) : bonus{bonus} {
  atk = 5;
  def = 10;
  HP = 70;
  gold = 1;
  position = p;
  symbol = 'N';
  race = "Goblin";
}

std::string Goblin::attack(Character *target) {
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
      int steal = randomNum(4);
      if (steal == 1) {
        int stolen = 0;
        if (target->getGold() > 0) {
          stolen = 1;
          target->setGold(target->getGold() - 1);
        }
        gold += stolen;
        msg = msg + symbol + " has stolen " + to_string(stolen) + " gold. ";
      }
    }
  } else {
    msg = msg + symbol + " missed. ";
  }
  return msg;
}

int Goblin::getAtk() { return atk; }

int Goblin::getDef() { return def; }