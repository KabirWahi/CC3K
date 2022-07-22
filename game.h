#ifndef GAME_H
#define GAME_H
#include <string>
#include <vector>

#include "enemy.h"
#include "item.h"
#include "player.h"
#include "posn.h"

class Game {
  Player *player;
  std::vector<Enemy *> enemies;
  std::vector<Item *> items;
  std::vector<std::vector<std::pair<int, int>>> mapPosns;
  Posn stairPosition;
  bool stairVisible;
  int level;
  int barrierFloor;
  bool newLevel = false;
  void generatePlayer(char symbol);  // generate player
  void generateEnemies();            // generate enemies and add to vector enemies
  void generateItems();              // generate items and add to vector items
  Posn randomPosn(int chamber);      // generate random valid posn
  Posn randomNeighbour(Posn posn);   // generate random neighbour of posn
 public:
  void changeMap(std::string filename);
  std::vector<std::vector<char>> defaultMap;
  std::vector<std::vector<char>> displayGrid;
  char playerSymbol;
  Game(char playerSymbol);            // constructor
  ~Game();                            // destructor
  void play();                        // play game
  void print();                       // print displayGrid
  std::string update();               // update displayGrid
  Player *getPlayer();                // return player pointer
  Posn getStairs();                   // return stairs position
  int getLevel();                     // return level
  void init();                        // initialize game
  void nextLevel();                   // go to next level
  void restart();                     // restart game
  bool neighborHasPlayer(Posn posn);  // return true if neighbor has player
};

#endif  // GAME_H
