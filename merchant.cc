#include "merchant.h"

#include <iostream>

using namespace std;

bool Merchant::hostile = false;

Merchant::Merchant(Posn p) {
  atk = 70;
  def = 5;
  HP = 30;
  gold = 0;
  position = p;
  symbol = 'M';
  race = "Merchant";
}

int Merchant::getAtk() { return atk; }

int Merchant::getDef() { return def; }

string Merchant::attack(Character *target) {
  if (!hostile) {
    return "";
  } else {
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

bool Merchant::isHostile() { return hostile; }

void Merchant::setHP(int HP) {
  this->HP = HP;
  hostile = true;
}

void Merchant::setHostile() { hostile = true; }
