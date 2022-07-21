#include "dwarf.h"

using namespace std;

Dwarf::Dwarf(Posn p) {
  knownPotions[0] = false;
  knownPotions[1] = false;
  knownPotions[2] = false;
  knownPotions[3] = false;
  knownPotions[4] = false;
  knownPotions[5] = false;
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