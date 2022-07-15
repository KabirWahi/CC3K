#ifndef GAME_H
#define GAME_H
#include <vector>
#include "posn.h"


class Game {
    Player * player;
    std::vector<Enemy*> enemies;
    std::vector<Item*> items;
    Posn stairPosition;
    bool stairVisible;
    int level;
    int barrierFloor;

    void generatePlayer(char symbol); // generate player
    void generateEnemies(); // generate enemies and add to vector enemies
    void generateItems(); // generate items and add to vector items

    public:
    std::vector<std::vector<char>> defaultMap;
    std::vector<std::vector<char>> displayGrid;
    char playerSymbol;

    Game(char playerSymbol); // constructor
    ~Game(); // destructor
    void play(); // play game
    void print(); // print displayGrid
    void update(); // update displayGrid
    Player *getPlayer(); // return player pointer
    Posn getStairs(); // return stairs position
    int getLevel(); // return level
    void init(); // initialize game
    void nextLevel(); // go to next level
};

#endif // GAME_H
