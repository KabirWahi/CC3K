#include "dragonhoard.h"
#include "gold.h"
#include "posn.h"
#include <string>
using namespace std;

DragonHoard::DragonHoard(char symbol, Posn position, string name, int value): Gold{symbol, position, name, value} {
    guarded = true;
}

DragonHoard::~DragonHoard() {}

bool DragonHoard::isGuarded() {
    return guarded;
}

void DragonHoard::setGuarded() {
    guarded = false;
}
