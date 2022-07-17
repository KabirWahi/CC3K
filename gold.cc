#include "item.h"
#include "gold.h"
#include "posn.h"
#include <string>
using namespace std;

Gold::Gold(char symbol, Posn position, string name, int value): Item{symbol, position}, name{name} {
    this->value = value;
}

Gold::~Gold() {}
