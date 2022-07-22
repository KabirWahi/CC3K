#ifndef ORC_H
#define ORC_H
#include "player.h"

class Orc : public Player {
 protected:
  int maxHP = 180;

 public:
  Orc(Posn p);
  void addGold(int amount) override;
};

#endif  // DWARF_H