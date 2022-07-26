#include "god.h"

using namespace std;

God::God(Posn p) {
  maxHP = 100;
  atk = 10000;
  def = 10000;
  HP = maxHP;
  gold = 9000;
  position = p;
  race = "God";
}

string God::attack(Character *target) {
  target->setHP(0);
  return "";
}
