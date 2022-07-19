#include "item.h"
#include "potion.h"
#include "posn.h"
#include <string>
using namespace std;

Potion::Potion(int id, Posn position): Item{id, position} {
    symbol = 'P';
    if (id == 0) {
        value = 10;
        name = "RH";
    } else if (id == 3) {
        value = -10;
        name = "PH";
    } else if (id == 1) {
        name = "BA";
    } else if (id == 2) {
        name = "BD";
    } else if (id == 4) {
        name = "WA";
    } else if (id == 5) {
        name = "WD";
    } else {} 
}

Potion::~Potion() {}
