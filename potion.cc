#include "item.h"
#include "potion.h"
#include "posn.h"
#include <string>
using namespace std;

Potion::Potion(char symbol, Posn position, string name, int value): Item{symbol, position}, name{name} {
    this->value = value;
}

Potion::~Potion() {}
