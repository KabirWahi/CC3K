#ifndef GOD_H
#define GOD_H
#include "player.h"
#include <string>

class God : public Player {
 public:
  God(Posn p);
  std::string attack(Character *target) override;
};


#endif // GOD_H
