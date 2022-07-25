#ifndef VALKYRIE_H
#define VALKYRIE_H
#include "player.h"

class Valkyrie : public Player {
 protected:
  int maxHP = 180;
 public:
  Valkyrie(Posn p);
};


#endif // VALKYRIE_H

