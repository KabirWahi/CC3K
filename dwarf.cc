#include "dwarf.h"

using namespace std;

Dwarf::Dwarf(Posn p) {
  atk = 20;
  def = 20;
  HP = maxHP;
  gold = 0;
  position = p;
  race = "Dwarf";
}

void Dwarf::addGold(int amount) {
    gold += (amount * 2);
}