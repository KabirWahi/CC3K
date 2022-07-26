#include "reverser.h"

#include <iostream>

using namespace std;

Reverser::Reverser(Posn p) {
  atk = 25;
  def = 25;
  HP = 40;
  gold = 1;
  position = p;
  symbol = 'R';
  race = "Reverser";
}

string Reverser::attack(Character *target) {
  int hit = randomNum(2);
  string msg = "";
  if (hit == 1) {
    int damage = target->getAtk();
    if (target->hasBarrier()) {
      damage = ceil(double(damage) / double(2));
    }
    target->setHP(target->getHP() - damage);
    msg = msg + symbol + " deals " + to_string(damage) + " damage to PC. ";
  } else {
    msg = msg + symbol + " missed. ";
  }
  return msg;
}

int Reverser::getAtk() { return atk; }

int Reverser::getDef() { return def; }
