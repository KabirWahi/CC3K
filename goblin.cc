#include "goblin.h"

#include <iostream>

using namespace std;

Goblin::Goblin(Posn p) {
  atk = 5;
  def = 10;
  HP = 70;
  gold = 1;
  position = p;
  symbol = 'N';
  race = "Goblin";
}

void Goblin::attack(Character *target) {
  int damage = ceil(double(100) / double(100 + target->getDef()) * atk);
  if (target->hasBarrier()) {
    damage = damage / 2;
  }
  target->setHP(target->getHP() - damage);
}

int Goblin::getAtk() { return atk; }

int Goblin::getDef() { return def; }