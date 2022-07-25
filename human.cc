#include "human.h"

#include <iostream>
using namespace std;

Human::Human(Posn p) {
  maxHP = 140;
  atk = 20;
  def = 20;
  maxHP = 140;
  HP = maxHP;
  gold = 0;
  position = p;
  race = "Human";
}