#include "player.h"

#include <algorithm>
#include <string>

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

string Player::attack(Character *target) {
  int damage = ceil(double(100) / double(100 + target->getDef()) * getAtk());
  target->setHP(target->getHP() - damage);
  return "PC deals " + to_string(damage) + " damage to " + target->getSymbol() +
         " (" + to_string(max(0, target->getHP())) + " HP). ";
}

bool Player::getknownPotions(int index) {
  return knownPotions[index];
}

void Player::toggleknownPotions(int index) {
  knownPotions[index] = true;
}

Player::~Player() {}