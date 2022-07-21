#ifndef POTION_H
#define POTION_H
#include <string>
#include "item.h"

class Potion: public Item {
    protected:
    std::string name;
    public:
    std::string getName();
    Potion(int id, Posn position);
    ~Potion();
};

#endif
