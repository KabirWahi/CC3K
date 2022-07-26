#include "valkyrie.h"

#include <iostream>
using namespace std;

Valkyrie::Valkyrie(Posn p) {
  maxHP = 180;
  atk = 35;
  def = 25;
  HP = maxHP;
  gold = 0;
  position = p;
  race = "Valkyrie";
}
