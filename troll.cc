#include "troll.h"

#include <iostream>

using namespace std;

Troll::Troll(Posn p) {
  atk = 25;
  def = 15;
  HP = 120;
  gold = 1;
  position = p;
  symbol = 'T';
  race = "Troll";
}

void Troll::attack(Character *target) {
  int damage = ceil(double(100) / double(100 + target->getDef()) * atk);
  if (target->hasBarrier()) {
    damage = ceil(double(damage) / double(2));
  }
  target->setHP(target->getHP() - damage);
}

int Troll::getAtk() { return atk; }

int Troll::getDef() { return def; }