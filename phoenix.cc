#include "phoenix.h"

#include <iostream>

using namespace std;

Phoenix::Phoenix(Posn p) {
  atk = 35;
  def = 20;
  HP = 50;
  gold = 1;
  position = p;
  symbol = 'X';
  race = "Phoenix";
}

int Phoenix::getAtk() { return atk; }

int Phoenix::getDef() { return def; }