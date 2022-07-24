#ifndef POSN_H
#define POSN_H

class Posn {
    int row;
    int col;

    public:
    Posn(int r = 0, int c = 0) {
        row = r;
        col = c;
    }
    int getRow() { return row; }
    int getCol() { return col; }
    bool operator==(const Posn &other) {
        return row == other.row && col == other.col;
    }
};

#endif // POSN_H
