#include "vampire.h"

#include <iostream>

using namespace std;

Vampire::Vampire(Posn p, bool bonus) : bonus{bonus} {
  atk = 25;
  def = 25;
  HP = 50;
  gold = 1;
  position = p;
  symbol = 'V';
  race = "Vampire";
}

string Vampire::attack(Character *target) {
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
      HP = HP + (damage / 5);
      msg = msg + symbol + " has lifesteal and healed " + to_string(damage / 5) + " HP (" + to_string(HP) + " HP). ";
    }
  } else {
    msg = msg + symbol + " missed. ";
  }
  return msg;
}

int Vampire::getAtk() { return atk; }

int Vampire::getDef() { return def; }
