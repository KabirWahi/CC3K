#ifndef GOLD_H
#define GOLD_H
#include <string>
#include "item.h"

class Gold: public Item {
    protected:
    std::string name;
    public:
    Gold(int id, Posn position);
    ~Gold();
};

#endif
