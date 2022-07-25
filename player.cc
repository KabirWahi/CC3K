#include "player.h"

#include <algorithm>
#include <string>

using namespace std;

void Player::toggleBarrier() { barrier = !barrier; }

bool Player::hasBarrier() const { return barrier; }

void Player::addGold(int amount) { gold += amount; }

void Player::addHealth(int amount) { HP = min(HP + amount, maxHP); }

string Player::attack(Character* target) {
  int damage = ceil(double(100) / double(100 + target->getDef()) * getAtk());
  target->setHP(target->getHP() - damage);
  return "PC deals " + to_string(damage) + " damage to " + target->getSymbol() +
         " (" + to_string(max(0, target->getHP())) + " HP). ";
}

bool Player::getknownPotions(int index) { return knownPotions[index]; }

void Player::toggleknownPotions(int index) { knownPotions[index] = true; }

std::string Player::usePotion(Item* item) {
  string msg = "";
  if (item->getId() == 0 || item->getId() == 3) {
    addHealth(item->getValue());
    cout << maxHP << endl;
    if (item->getId() == 0) {
      msg = "PC picked up a RH potion. ";
    } else {
      msg = "PC picked up a PH potion. ";
    }
  }
  if (item->getId() == 1) {
    msg = "PC picked up a BA potion. ";
  }
  if (item->getId() == 2) {
    msg = "PC picked up a BD potion. ";
  }
  if (item->getId() == 4) {
    msg = "PC picked up a WA potion. ";
  }
  if (item->getId() == 5) {
    msg = "PC picked up a WD potion. ";
  }
  return msg;
}

Player::~Player() {}