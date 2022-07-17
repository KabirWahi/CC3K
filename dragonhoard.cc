#include "dragonhoard.h"
#include "gold.h"
#include "posn.h"
#include <string>
using namespace std;

DragonHoard::DragonHoard(Posn position): Gold{position, "DragonHoard"} {
    value = 6;
    guarded = true;
}

DragonHoard::~DragonHoard() {}

bool DragonHoard::isGuarded() {
    return guarded;
}

void DragonHoard::setGuarded() {
    guarded = false;
}
