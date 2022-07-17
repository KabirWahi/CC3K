#include "werewolf.h"

#include <iostream>

using namespace std;

Werewolf::Werewolf(Posn p) {
  atk = 25;
  def = 25;
  HP = 50;
  gold = 1;
  position = p;
  symbol = 'W';
  race = "Werewolf";
}

void Werewolf::attack(Character *target) {
  int damage = ceil(double(100) / double(100 + target->getDef()) * atk);
  target->setHP(target->getHP() - damage);
  cout << symbol << " deals " << damage << " damage to PC. ";
}

int Werewolf::getAtk() {
  return atk;
}

int Werewolf::getDef() {
  return def;
}