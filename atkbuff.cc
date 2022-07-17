#include "atkbuff.h"
#include "buff.h"
#include "math.h"
#include <string>
using namespace std;

AtkBuff::AtkBuff(Player* player, string name): Buff{player} {
    this->name = name;
    if (name == "BA") {
        value = 5;
    } else if (name == "WA") {
        value = -5;
    } else {
        value = 0;
    }
    string playerRace = player->getRace();
    if (playerRace == "Elf") {
        value = abs(value);
    }
}

AtkBuff::~AtkBuff() {}

int AtkBuff::getAtk() {
    return value + player->getAtk();
}
    
int AtkBuff::getDef() {
    return player->getDef();
}
