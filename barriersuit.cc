#include "barriersuit.h"
#include "item.h"
#include "posn.h"

BarrierSuit::BarrierSuit(Posn position): Item{10, position} {
    symbol = 'B';
    guarded = true;
}

BarrierSuit::~BarrierSuit() {}

void BarrierSuit::setGuarded() {
    guarded = false;
}
