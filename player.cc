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
    setHP(min(getHP() + amount, maxHP));
}

void Player::attack(Character *target) {
  int damage = ceil(double(100) / double(100 + target->getDef()) * getAtk());
  target->setHP(target->getHP() - damage);
}

bool Player::getknownPotions(int index) {
    return knownPotions[index];
}

void Player::toggleknownPotions(int index) {
    knownPotions[index] = true;
}

Player::~Player() {}