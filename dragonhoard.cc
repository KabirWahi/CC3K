#include "dragonhoard.h"
#include "gold.h"
#include "posn.h"
#include <string>
using namespace std;

DragonHoard::DragonHoard(Posn position): Gold{9, position} {
    symbol = 'G';
    value = 6;
    name = "DragonHoard";
    guarded = true;
}

DragonHoard::~DragonHoard() {}
