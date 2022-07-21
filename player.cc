#include "player.h"
#include <algorithm>

using namespace std;

void Player::toggleBarrier() {
    barrier = !barrier;
}

bool Player::hasBarrier() const {
    return barrier;
}

void Player::addGold(int amount) {
    gold += amount;
}

void Player::addHealth(int amount) {
    HP = max(0, min(HP + amount, maxHP));
}

void Player::attack(Character *target) {
  int damage = ceil(double(100) / double(100 + target->getDef()) * getAtk());
  target->setHP(target->getHP() - damage);
}

Player::~Player() {}