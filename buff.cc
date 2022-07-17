#include "buff.h"
#include "player.h"

Buff::Buff(Player* player): player{player} {}

Buff::~Buff() {
    delete player;
}
