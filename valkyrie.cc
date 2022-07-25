#include "valkyrie.h"

#include <iostream>
using namespace std;

Valkyrie::Valkyrie(Posn p) {
  atk = 40;
  def = 40;
  HP = maxHP;
  gold = 0;
  position = p;
  race = "Valkyrie";
}