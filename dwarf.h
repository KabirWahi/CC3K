#ifndef DWARF_H
#define DWARF_H
#include "player.h"

class Dwarf : public Player {
 protected:
  int maxHP = 100;

 public:
  Dwarf(Posn p);
  void addGold(int amount) override;
};

#endif  // DWARF_H