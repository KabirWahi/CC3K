#include "defbuff.h"
#include "buff.h"
#include <string>
using namespace std;

DefBuff::DefBuff(Player* player, string name): Buff{player} {
    this->name = name;
    if (name == "BD") {
        value = 5;
    } else if (name == "WD") {
        value = -5;
    } else {
        value = 0;
    }
    string playerRace = player->getRace();
    if (playerRace == "Elf") {
        value = abs(value);
    }
} 


int DefBuff::getDef() {
    return value + player->getDef();
}

bool DefBuff::getknownPotions(int index) {
    return player->getknownPotions(index);
}

void DefBuff::toggleknownPotions(int index) {
    player->toggleknownPotions(index);
}