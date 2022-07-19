#ifndef COMPASS_H
#define COMPASS_H
#include "item.h"

class Compass : public Item {
    public:
    Compass(Posn position);
    ~Compass();
};

#endif
