#ifndef ELF_H
#define ELF_H
#include "player.h"

class Elf : public Player {
 public:
  Elf(Posn p);
  void addHealth(int amount) override;
};

#endif  // ELF_H