#include "player.h"

void Player::toggleBarrier() {
    barrier = !barrier;
}

bool Player::hasBarrier() const {
    return barrier;
}