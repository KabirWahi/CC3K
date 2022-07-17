#include "item.h"
#include "gold.h"
#include "posn.h"
#include <string>
using namespace std;

Gold::Gold(char symbol, Posn position): Item{symbol, position} {
    if (symbol == '6') {
        value = 1;
        name = "Normal";
    } else if (symbol = '7') {
        value = 2;
        name = "SmallHoard";
    } else if (symbol = '8') {
        value = 4;
        name == "MerchantHoard";
    } else {}
}

Gold::~Gold() {}
