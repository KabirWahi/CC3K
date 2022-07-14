#ifndef CHARACTER_H
#define CHARACTER_H
#include "posn.h"

class Character {
    protected:
    int HP;
    int atk;
    int def;
    int gold;
    const char symbol;
    Posn position;
    int whichChamber;

    public:
    ~Character(); // destructor
    virtual int getAtk(); // return atk
    virtual int getDef(); // return def
    int getHP(); // return HP
    int getGold(); // return gold
    Posn getPosition(); // return position
    char getSymbol(); // return symbol
    void move(int direction); // move character and update position
    void setPosition(Posn position); // set position
    virtual void attack(Character *target) = 0; // attack target
    virtual void beAttacked(int atk) = 0; // be attacked by atk and update HP
    void setHP(int HP); // set HP
    void setGold(int gold); // set gold
    void setAtk(int atk); // set atk
    void setDef(int def); // set def
};

#endif // CHARACTER_H