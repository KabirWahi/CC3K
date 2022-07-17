#include "item.h"
#include "gold.h"
#include "posn.h"
#include <string>
using namespace std;

Gold::Gold(Posn position, string name): Item{' ', position}, name{name} {
    if (name == "Normal") {
        value = 1;
        symbol = 6;
    } else if (name == "SmallHoard") {
        value = 2;
        symbol = 7;
    } else if (name == "MerchantHoard") {
        value = 4;
        symbol = 8;
    } else {}
}

Gold::~Gold() {}
