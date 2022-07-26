#include "enemy.h"

#include <string>

using namespace std;

string Enemy::attack(Character *target) {
  int hit = randomNum(2);
  string msg = "";
  if (hit == 1) {
    int damage = ceil(double(100) / double(100 + target->getDef()) * atk);
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
