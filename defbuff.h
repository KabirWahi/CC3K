#ifndef DEFBUFF_H
#define DEFBUFF_H
#include "buff.h"
#include "player.h"
#include "math.h"
#include <string>

class DefBuff: public Buff {
    public:
    DefBuff(Player* player, std::string name);
    virtual ~DefBuff();
    int getDef() override;
    virtual bool getknownPotions(int index) override;
    virtual void toggleknownPotions(int index) override;
};

#endif
