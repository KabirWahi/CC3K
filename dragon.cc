#include "dragon.h"

#include <iostream>

using namespace std;

Dragon::Dragon(Posn p, Item *i) : guarding(i) {
  atk = 20;
  def = 20;
  HP = 150;
  gold = 0;
  position = p;
  symbol = 'D';
  race = "Dragon";
}

void Dragon::attack(Character *target) {
  int damage = ceil(double(100) / double(100 + target->getDef()) * atk);
  if (target->hasBarrier()) {
    damage = ceil(double(damage) / double(2));
  }
  target->setHP(target->getHP() - damage);
}

int Dragon::getAtk() { return atk; }

int Dragon::getDef() { return def; }

Item * Dragon::getItem() { return guarding; }