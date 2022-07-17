#ifndef BARRIERSUIT_H
#define BARRIERSUIT_H
#include "item.h"

class BarrierSuit: public Item {
    public:
    BarrierSuit(Posn position);
    ~BarrierSuit();
    bool isGuarded() override;
    void setGuarded() override;
};

#endif
