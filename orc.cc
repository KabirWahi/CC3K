#include "orc.h"

using namespace std;

Orc::Orc(Posn p) {
  maxHP = 180;
  atk = 30;
  def = 25;
  HP = maxHP;
  gold = 0;
  position = p;
  race = "Dwarf";
}

void Orc::addGold(int amount) {
    gold += ceil(double(amount) / double(2));
}