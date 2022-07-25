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
  bool bonus = false;
  std::vector<Enemy *> enemies;
  std::vector<Item *> items;
  std::vector<std::vector<std::pair<int, int>>> mapPosns;
  std::vector<std::vector<char>> defaultMap;
  std::vector<std::vector<char>> displayGrid;
  int height;
  int width;
  char playerSymbol;
  int playerStartChamber;
  int level;
  Posn stairPosition;
  bool stairVisible;
  int barrierFloor;
  int chamberCount;
  bool newLevel = false;
  void generatePlayer(char symbol);   // generate player
  void generateEnemies();             // generate enemies and add to vector enemies
  void generateItems();               // generate items and add to vector items
  void init();                        // initialize game
  void nextLevel();                   // go to next level
  void restart();                     // restart game
  bool neighborHasPlayer(Posn posn);  // return true if neighbor has player
  void print();                       // print displayGrid
  Posn randomPosn(int chamber);       // generate random valid posn
  Posn randomNeighbour(Posn posn);    // generate random neighbour of posn
  std::string update();               // update displayGrid
  Player *getPlayer();                // return player pointer
  Posn getStairs();                   // return stairs position
  int getLevel();                     // return level

 public:
  void changeMap(std::string filename);
  Game(char playerSymbol, bool bonus);            // constructor
  ~Game();                            // destructor
  void play();                        // play game
};

#endif  // GAME_H
