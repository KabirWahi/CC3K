#include "compass.h"

Compass::Compass(Posn position) : Item{11, position} {
  symbol = 'C';
}

Compass::~Compass() {}
