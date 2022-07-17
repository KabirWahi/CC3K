#include "merchant.h"

#include <iostream>

using namespace std;

Merchant::Merchant(Posn p) {
  atk = 25;
  def = 25;
  HP = 50;
  gold = 1;
  position = p;
  symbol = 'M';
  race = "Merchant";
}

void Merchant::attack(Character *target) {
  int damage = ceil(double(100) / double(100 + target->getDef()) * atk);
  target->setHP(target->getHP() - damage);
  cout << symbol << " deals " << damage << " damage to PC. ";
}

int Merchant::getAtk() {
  return atk;
}

int Merchant::getDef() {
  return def;
}