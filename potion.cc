#include "item.h"
#include "potion.h"
#include "posn.h"
#include <string>
using namespace std;

Potion::Potion(Posn position, string name): Item{'P', position}, name{name} {
    if (name == "RH") {
        value = 10;
    } else if (name == "PH") {
        value = -10;
    } else {
        value = 0;
    }
}

Potion::~Potion() {}
