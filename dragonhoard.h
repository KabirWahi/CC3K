#ifndef DRAGONHOARD_H
#define DRAGONHOARD_H
#include <string>
#include "gold.h"

class DragonHoard: public Gold {
    public:
    DragonHoard(Posn position);
    ~DragonHoard();
    void setGuarded() override;
};

#endif
