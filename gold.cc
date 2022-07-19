#include "item.h"
#include "gold.h"
#include "posn.h"
#include <string>
using namespace std;

Gold::Gold(int id, Posn position): Item{id, position} {
    symbol = 'G';
    if (id == 6) {
        value = 1;
        name = "Normal";
    } else if (id = 7) {
        value = 2;
        name = "SmallHoard";
    } else if (id = 8) {
        value = 4;
        name == "MerchantHoard";
    } else {}
}

Gold::~Gold() {}
