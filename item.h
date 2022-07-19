#ifndef ITEM_H
#define ITEM_H
#include "posn.h"

class Item {
    protected:
    char symbol;
    Posn position;
    int value;  
    bool guarded;
    int id;

    public:
    Item(int id, Posn position);
    virtual ~Item() = 0;
    char getSymbol(); // return symbol
    Posn getPosition(); // return position
    int getValue(); // return value
    bool isGuarded(); // for a DragonHoard/BarrierSuit, if it is guarded by a dragon
    virtual void setGuarded(bool value); // for a DragonHoard/BarrierSuit, set false if the dragon is dead

};

#endif
