#include "barriersuit.h"
#include "item.h"
#include "posn.h"

BarrierSuit::BarrierSuit(char symbol, Posn position): Item{symbol, position} {
    guarded = true;
}

BarrierSuit::~BarrierSuit() {}

bool BarrierSuit::isGuarded() {
    return guarded;
}

void BarrierSuit::setGuarded() {
    guarded = false;
}
