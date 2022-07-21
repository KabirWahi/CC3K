#include "item.h"
#include "posn.h"

Item::Item(int id, Posn position): id{id}, position{position}, value{0}, guarded{false} {}

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

int Item::getId() {
    return id;
}
    
bool Item::isGuarded() {
    return guarded;
}

void Item::setGuarded(bool value) {
    guarded = value;
}
