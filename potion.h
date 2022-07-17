#ifndef POTION_H
#define POTION_H
#include <string>
#include "item.h"

class Potion: public Item {
    protected:
    std::string name;
    public:
    Potion(char symbol, Posn position, std::string name, int value);
    ~Potion();
};

#endif
