#include "goblin.h"

#include <iostream>

using namespace std;

Goblin::Goblin(Posn p) {
  atk = 25;
  def = 25;
  HP = 50;
  gold = 1;
  position = p;
  symbol = 'N';
  race = "Goblin";
}

void Goblin::attack(Character *target) {
  int damage = ceil(double(100) / double(100 + target->getDef()) * atk);
  target->setHP(target->getHP() - damage);
}

int Goblin::getAtk() {
  return atk;
}

int Goblin::getDef() {
  return def;
}