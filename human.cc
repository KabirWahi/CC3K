#include "human.h"

#include <iostream>
using namespace std;

Human::Human(Posn p) {
  atk = 20;
  def = 20;
  HP = maxHP;
  gold = 0;
  position = p;
  race = "Human";
}

void Human::attack(Character *target) {
  int damage = ceil((100 / (100 + target->getDef())) * atk);
  target->setHP(target->getHP() - damage);
  cout << "PC deals " << damage << " damage to " << target->getSymbol() << " (" << target->getHP() << " HP). ";
}

int Human::getAtk() {
  return atk;
}

int Human::getDef() {
  return def;
}