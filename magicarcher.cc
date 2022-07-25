#include "magicarcher.h"

using namespace std;

MagicArcher::MagicArcher(Posn p) {
  atk = 35;
  def = 20;
  HP = maxHP;
  gold = 0;
  position = p;
  race = "Magic Archer";
}