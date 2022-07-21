#include "vampire.h"

#include <iostream>

using namespace std;

Vampire::Vampire(Posn p) {
  atk = 25;
  def = 25;
  HP = 50;
  gold = 1;
  position = p;
  symbol = 'V';
  race = "Vampire";
}

void Vampire::attack(Character *target) {
  int damage = ceil(double(100) / double(100 + target->getDef()) * atk);
  if (target->hasBarrier()) {
    damage = ceil(double(damage) / double(2));
  }
  target->setHP(target->getHP() - damage);
}

int Vampire::getAtk() { return atk; }

int Vampire::getDef() { return def; }