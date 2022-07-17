#ifndef POTION_H
#define POTION_H
#include <string>
#include "item.h"

class Potion: public Item {
    protected:
    std::string name;
    public:
    Potion(Posn position, std::string name);
    ~Potion();
};

#endif
