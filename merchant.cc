#include "merchant.h"

#include <iostream>

using namespace std;

bool Merchant::hostile = false;

Merchant::Merchant(Posn p) {
  atk = 70;
  def = 5;
  HP = 30;
  gold = 0;
  position = p;
  symbol = 'M';
  race = "Merchant";
}

void Merchant::attack(Character *target) {
  int damage = ceil(double(100) / double(100 + target->getDef()) * atk);
  if (target->hasBarrier()) {
    damage = ceil(double(damage) / double(2));
  }
  target->setHP(target->getHP() - damage);
}

int Merchant::getAtk() { return atk; }

int Merchant::getDef() { return def; }

bool Merchant::isHostile() { return hostile; }

void Merchant::setHostile() { hostile = true; }