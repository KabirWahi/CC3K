#ifndef DWARF_H
#define DWARF_H
#include "player.h"

class Dwarf : public Player {
 public:
  Dwarf(Posn p);
  void addGold(int amount) override;
};

#endif  // DWARF_H
