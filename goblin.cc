#include "goblin.h"

#include <iostream>

using namespace std;

Goblin::Goblin(Posn p) {
  atk = 5;
  def = 10;
  HP = 70;
  gold = 1;
  position = p;
  symbol = 'N';
  race = "Goblin";
}

int Goblin::getAtk() { return atk; }

int Goblin::getDef() { return def; }