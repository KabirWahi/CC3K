#ifndef ITEM_H
#define ITEM_H
#include "posn.h"

class Item {
    protected:
    char symbol;
    Posn position;
    bool guarded;

    public:
    void getSymbol(); // return symbol
    Posn getPosition(); // return position
    bool isGuarded(); // for a DragonHoard, if it is guarded by a dragon

};

#endif
