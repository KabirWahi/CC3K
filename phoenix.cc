#include "phoenix.h"

#include <iostream>

using namespace std;

Phoenix::Phoenix(Posn p) {
  atk = 25;
  def = 25;
  HP = 50;
  gold = 1;
  position = p;
  symbol = 'X';
  race = "Phoenix";
}

void Phoenix::attack(Character *target) {
  int damage = ceil(double(100) / double(100 + target->getDef()) * atk);
  target->setHP(target->getHP() - damage);
}

int Phoenix::getAtk() {
  return atk;
}

int Phoenix::getDef() {
  return def;
}