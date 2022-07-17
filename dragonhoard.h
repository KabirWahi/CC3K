#ifndef DRAGONHOARD_H
#define DRAGONHOARD_H
#include <string>
#include "gold.h"

class DragonHoard: public Gold {
    public:
    DragonHoard(char symbol, Posn position, std::string name, int value);
    ~DragonHoard();
    bool isGuarded() override;
    void setGuarded() override;
};

#endif
