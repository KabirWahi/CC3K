#include "werewolf.h"

#include <iostream>

using namespace std;

Werewolf::Werewolf(Posn p) {
  atk = 30;
  def = 5;
  HP = 120;
  gold = 1;
  position = p;
  symbol = 'W';
  race = "Werewolf";
}

int Werewolf::getAtk() { return atk; }

int Werewolf::getDef() { return def; }
