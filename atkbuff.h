#ifndef ATKBUFF_H
#define ATKBUFF_H
#include "buff.h"
#include "player.h"
#include <string>

class AtkBuff: public Buff {
    public:
    AtkBuff(Player* player, std::string name);
    virtual ~AtkBuff();
    int getAtk() override;
    int getDef() override;
    virtual bool getknownPotions(int index) override;
    virtual void toggleknownPotions(int index) override;
};

#endif
