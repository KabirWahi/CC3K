#ifndef BUFF_H
#define BUFF_H
#include "player.h"
#include <string>

class Buff: public Player {
    protected:
    Player* player;
    int value;
    std::string name;

    public:
    Buff(Player* player);
    virtual ~Buff();
    virtual int getAtk() = 0;
    virtual int getDef() = 0;
};

#endif
