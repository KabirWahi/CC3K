#include "character.h"

#include <string>
#include <algorithm>

using namespace std;

int Character::getAtk() {
  return max(0, atk);
}

int Character::getDef() {
  return max(0, def);
}

int Character::getHP() {
  return HP;
}

int Character::getGold() {
  return gold;
}

Posn Character::getPosition() {
  return position;
}

char Character::getSymbol() {
  return symbol;
}

string Character::getRace() {
  return race;
}

void Character::setPosition(Posn p) {
  position = p;
}

void Character::setAtk(int atk) {
  this->atk = atk;
}

void Character::setDef(int def) {
  this->def = def;
}

void Character::setHP(int HP) {
  this->HP = HP;
}

void Character::setGold(int gold) {
  this->gold = gold;
}
