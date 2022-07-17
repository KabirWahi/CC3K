#include "item.h"
#include "potion.h"
#include "posn.h"
#include <string>
using namespace std;

Potion::Potion(char symbol, Posn position): Item{symbol, position} {
    if (symbol == '0') {
        value = 10;
        name = "RH";
    } else if (symbol == '3') {
        value = -10;
        name = "PH";
    } else if (symbol == '1') {
        name = "BA";
    } else if (symbol == '2') {
        name = "BD";
    } else if (symbol == '4') {
        name = "WA";
    } else if (symbol == '5') {
        name = "WD";
    } else {} 
}

Potion::~Potion() {}
