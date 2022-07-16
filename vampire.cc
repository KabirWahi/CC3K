#include "vampire.h"

#include <iostream>

using namespace std;

Vampire::Vampire(Posn p) {
  atk = 25;
  def = 25;
  HP = 50;
  position = p;
  symbol = 'V';
  race = "Vampire";
}

void Vampire::attack(Character *target) {
  int damage = ceil(double(100) / double(100 + target->getDef()) * atk);
  target->setHP(target->getHP() - damage);
  cout << symbol << " deals " << damage << " damage to PC and stole " << (damage / 5) << " HP from PC. ";
  // lifesteal
  HP += (damage / 5);
}

int Vampire::getAtk() {
  return atk;
}

int Vampire::getDef() {
  return def;
}