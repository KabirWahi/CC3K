#ifndef POTION_H
#define POTION_H
#include <string>
#include "item.h"

class Potion: public Item {
    public:
    std::string getName();
    Potion(int id, Posn position);
    ~Potion();
};

#endif
