#include "item.h"
#include "gold.h"
#include "posn.h"
#include <string>
using namespace std;

Gold::Gold(Posn position, string name): Item{'G', position}, name{name} {
    if (name == "Normal") {
        value = 1;
    } else if (name == "SmallHoard") {
        value = 2;
    } else if (name == "MerchantHoard") {
        value = 4;
    } else {
        value = 0;
    }
}

Gold::~Gold() {}
