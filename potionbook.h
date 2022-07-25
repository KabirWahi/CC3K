#ifndef POTIONBOOK_H
#define POTIONBOOK_H
#include <string>
#include "item.h"

class PotionBook: public Item {
    protected:
    std::string name;
    public:
    PotionBook(Posn position);
    ~PotionBook();
};

#endif
