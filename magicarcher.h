#ifndef MAGICARCHER_H
#define MAGICARCHER_H
#include "player.h"

class MagicArcher : public Player {
 protected:
  int maxHP = 140;
 public:
  MagicArcher(Posn p);
};


#endif // MAGICARCHER_H