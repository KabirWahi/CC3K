#ifndef POSN_H
#define POSN_H

class Posn {
    public:
    int row;
    int col;
    bool operator==(const Posn &other) {
        return row == other.row && col == other.col;
    }
    int whichChamber();
};

#endif // POSN_H
