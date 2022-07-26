#include "dragon.h"

#include <iostream>

using namespace std;

Dragon::Dragon(Posn p, Item *i) : guarding(i) {
  atk = 20;
  def = 20;
  HP = 150;
  gold = 0;
  position = p;
  symbol = 'D';
  race = "Dragon";
}

int Dragon::getAtk() { return atk; }

int Dragon::getDef() { return def; }

string Dragon::attack(Character *target) {
  for (int i = 0; i < 8; i++) {
    if (getItem()->getPosition().getRow() == target->getPosition().getRow() + r[i] &&
        getItem()->getPosition().getCol() == target->getPosition().getCol() + c[i]) {
      int hit = randomNum(2);
      string msg = "";
      if (hit == 1) {
        int damage = ceil(double(100) / double(100 + target->getDef()) * atk);
        if (target->hasBarrier()) {
          damage = ceil(double(damage) / double(2));
        }
        target->setHP(target->getHP() - damage);
        msg = msg + symbol + " deals " + to_string(damage) + " damage to PC. ";
      } else {
        msg = msg + symbol + " missed. ";
      }
      return msg;
    }
  }
  return "";
}

Item *Dragon::getItem() { return guarding; }
