#include "item.h"
#include "potionbook.h"
#include "posn.h"
#include <string>
using namespace std;

PotionBook::PotionBook(Posn position): Item{9, position} {
    symbol = 'K';
}

PotionBook::~PotionBook() {}
