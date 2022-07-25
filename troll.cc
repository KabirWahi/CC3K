#include "troll.h"

#include <iostream>

using namespace std;

Troll::Troll(Posn p) {
  atk = 25;
  def = 15;
  HP = 120;
  gold = 1;
  position = p;
  symbol = 'T';
  race = "Troll";
}

int Troll::getAtk() { return atk; }

int Troll::getDef() { return def; }