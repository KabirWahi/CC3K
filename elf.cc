#include "elf.h"

#include <iostream>
#include <algorithm>
using namespace std;

Elf::Elf(Posn p) {
  maxHP = 140;
  atk = 30;
  def = 10;
  HP = maxHP;
  gold = 0;
  position = p;
  race = "Elf";
}

void Elf::addHealth(int amount) {
  if (amount < 0) {
    amount = - amount;
  }
  setHP(min(getHP() + amount, maxHP));
}
