#ifndef BARRIERSUIT_H
#define BARRIERSUIT_H
#include "item.h"

class BarrierSuit: public Item {
    public:
    BarrierSuit(Posn position);
    ~BarrierSuit();
    void setGuarded() override;
};

#endif
