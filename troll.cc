#include "troll.h"

#include <iostream>

using namespace std;

Troll::Troll(Posn p) {
  atk = 25;
  def = 25;
  HP = 50;
  gold = 1;
  position = p;
  symbol = 'T';
  race = "Troll";
}

void Troll::attack(Character *target) {
  int damage = ceil(double(100) / double(100 + target->getDef()) * atk);
  target->setHP(target->getHP() - damage);
  cout << symbol << " deals " << damage << " damage to PC. ";
}

int Troll::getAtk() {
  return atk;
}

int Troll::getDef() {
  return def;
}