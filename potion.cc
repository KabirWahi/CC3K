#include "item.h"
#include "potion.h"
#include "posn.h"
#include <string>
using namespace std;

Potion::Potion(Posn position, string name): Item{' ', position}, name{name} {
    if (name == "RH") {
        value = 10;
        symbol = '0';
    } else if (name == "PH") {
        value = -10;
        symbol = '3';
    } else if (name == "BA") {
        symbol = '1';
    } else if (name == "BD") {
        symbol = '2';
    } else if (name == "WA") {
        symbol = '4';
    } else if (name == "WD") {
        symbol = '5';
    } else {} 
}

Potion::~Potion() {}
