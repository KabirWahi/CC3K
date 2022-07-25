#ifndef ORC_H
#define ORC_H
#include "player.h"

class Orc : public Player {
 public:
  Orc(Posn p);
  void addGold(int amount) override;
};

#endif  // DWARF_H