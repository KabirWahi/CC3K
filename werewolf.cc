#include "werewolf.h"

#include <iostream>

using namespace std;

Werewolf::Werewolf(Posn p) {
  atk = 30;
  def = 5;
  HP = 120;
  gold = 1;
  position = p;
  symbol = 'W';
  race = "Werewolf";
}

void Werewolf::attack(Character *target) {
  int damage = ceil(double(100) / double(100 + target->getDef()) * atk);
  if (target->hasBarrier()) {
    damage = ceil(double(damage) / double(2));
  }
  target->setHP(target->getHP() - damage);
}

int Werewolf::getAtk() { return atk; }

int Werewolf::getDef() { return def; }
