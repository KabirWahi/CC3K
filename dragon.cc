#include "dragon.h"

#include <iostream>

using namespace std;

Dragon::Dragon(Posn p) {
  atk = 25;
  def = 25;
  HP = 50;
  gold = 1;
  position = p;
  symbol = 'D';
  race = "Dragon";
}

void Dragon::attack(Character *target) {
  int damage = ceil(double(100) / double(100 + target->getDef()) * atk);
  target->setHP(target->getHP() - damage);
  cout << symbol << " deals " << damage << " damage to PC. ";
}

int Dragon::getAtk() {
  return atk;
}

int Dragon::getDef() {
  return def;
}