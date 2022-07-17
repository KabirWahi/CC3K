#include "item.h"
#include "posn.h"

Item::Item(char symbol, Posn position): symbol{symbol}, position{position}, value{0}, guarded{false} {}

Item::~Item() {}

char Item::getSymbol() {
    return symbol;
}
    
Posn Item::getPosition() {
    return position;
}
    
int Item::getValue() {
    return value;
}
    
bool Item::isGuarded() {
    return guarded;
}

void Item::setGuarded() {
    return;
}
