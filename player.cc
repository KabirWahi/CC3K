#include "player.h"

void Player::toggleBarrier() {
    barrier = !barrier;
}

bool Player::hasBarrier() {
    return barrier;
}