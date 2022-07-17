#include "barriersuit.h"
#include "item.h"
#include "posn.h"

BarrierSuit::BarrierSuit(Posn position): Item{'B', position} {
    guarded = true;
}

BarrierSuit::~BarrierSuit() {}

bool BarrierSuit::isGuarded() {
    return guarded;
}

void BarrierSuit::setGuarded() {
    guarded = false;
}
