#include "dragonhoard.h"
#include "gold.h"
#include "posn.h"
#include <string>
using namespace std;

DragonHoard::DragonHoard(Posn position): Gold{position, "DragonHoard"} {
    value = 6;
    symbol = '9';
    guarded = true;
}

DragonHoard::~DragonHoard() {}

void DragonHoard::setGuarded() {
    guarded = false;
}
