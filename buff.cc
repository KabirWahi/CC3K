#include "buff.h"

#include "player.h"

Buff::Buff(Player* player) : player{player} {}

Buff::~Buff() {
  delete player;
}

void Buff::attack(Character* target) {
  player->attack(target);
}

void Buff::addGold(int amount) {
  player->addGold(amount);
}

void Buff::addHealth(int amount) {
  player->addHealth(amount);
}

bool Buff::hasBarrier() {
  return player->hasBarrier();
}

void Buff::toggleBarrier() {
  player->toggleBarrier();
}

int Buff::getHP() {
  return player->getHP();
}

int Buff::getGold() {
  return player->getGold();
}

Posn Buff::getPosition() {
  return player->getPosition();
}

char Buff::getSymbol() {
  return player->getSymbol();
}

std::string Buff::getRace() {
  return player->getRace();
}

void Buff::setPosition(Posn position) {
  player->setPosition(position);
}

void Buff::setHP(int HP) {
  player->setHP(HP);
}

void Buff::setGold(int gold) {
  player->setGold(gold);
}

void Buff::setAtk(int atk) {
  player->setAtk(atk);
}

void Buff::setDef(int def) {
  player->setDef(def);
}