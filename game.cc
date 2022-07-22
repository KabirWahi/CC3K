#include "game.h"

#include <time.h>

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>

#include "depends.h"

using namespace std;

const string movement[8] = {"no", "so", "ea", "we", "ne", "nw", "se", "sw"};
const int r[8] = {-1, 1, 0, 0, -1, -1, 1, 1};
const int c[8] = {0, 0, 1, -1, 1, -1, 1, -1};
const string directions[8] = {"North", "South", "East",
                              "West", "Northeast", "Northwest",
                              "Southeast", "Southwest"};

int randomNum(int upperBound) {
  std::vector<int> v;
  for (int i = 0; i < upperBound; i++) {
    v.push_back(i);
  }
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine rng{seed};
  std::shuffle(v.begin(), v.end(), rng);
  return v[0];
}

void Game::changeMap(string filename) {
  ifstream file(filename);
  vector<string> map;
  string line;
  while (getline(file, line)) {
    map.push_back(line);
  }
  for (int i = 0; i < 25; i++) {
    defaultMap.push_back(vector<char>());
    for (int j = 0; j < 79; j++) {
      defaultMap[i].push_back(map[i][j]);
    }
  }
  displayGrid = defaultMap;
  file.close();
  mapPosns = mapDetection(map);
}

Game::Game(char playerSymbol) : playerSymbol(playerSymbol), level(1), stairVisible(false), barrierFloor{randomNum(5) + 1} {}

void Game::init() {
  generatePlayer(playerSymbol);
  int chamber = randomNum(5) + 1;
  while (chamber == player->getPosition().whichChamber()) {
    chamber = randomNum(5) + 1;
  }
  stairPosition = randomPosn(chamber);
  displayGrid[stairPosition.row][stairPosition.col] = '\\';
  generateItems();
  generateEnemies();
  displayGrid[stairPosition.row][stairPosition.col] = '.';
}

Posn Game::randomPosn(int chamber) {
  chamber--;
  int sz = mapPosns[chamber].size();
  int r = randomNum(sz);
  int row = mapPosns[chamber][r].first;
  int col = mapPosns[chamber][r].second;
  while (displayGrid[row][col] != '.') {
    r = randomNum(sz);
    row = mapPosns[chamber][r].first;
    col = mapPosns[chamber][r].second;
  }
  return Posn{row, col};
}

Posn Game::randomNeighbour(Posn posn) {
  int row = posn.row;
  int col = posn.col;
  int neighbour = randomNum(8);
  row += r[neighbour];
  col += c[neighbour];
  while (displayGrid[row][col] != '.') {
    row = posn.row;
    col = posn.col;
    neighbour = randomNum(8);
    row += r[neighbour];
    col += c[neighbour];
  }
  return Posn{row, col};
}

void Game::play() {
  init();
  print();
  cout << "PC has spawned in the dungeon." << endl;
  string input;
  string msg = "";
  while (cin >> input) {
    bool moved = false;
    for (int i = 0; i < 8; i++) {
      if (input == movement[i]) {
        char tmp = displayGrid[player->getPosition().row + r[i]]
                              [player->getPosition().col + c[i]];
        if (tmp == '.' || tmp == '+' || tmp == '#' || tmp == '\\') {
          moved = true;
          player->setPosition(Posn{player->getPosition().row + r[i],
                                   player->getPosition().col + c[i]});
          displayGrid[player->getPosition().row][player->getPosition().col] = '@';
          if (player->getPosition() == stairPosition) {
            if (level == 5) {
              cout << "congratulations! You have reached the end of the dungeon." << endl;
              cout << "Your score is " << player->getGold() << "." << endl;
              return;
            }
            nextLevel();
            newLevel = true;
            msg = "You found the stairs! Welcome to the next floor!";
          } else {
            msg = "You moved " + directions[i] + ". ";
          }
          break;
        } else if (tmp == 'G') {
          for (int j = 0; j < items.size(); j++) {
            if (items[j]->getPosition().row == player->getPosition().row + r[i] &&
                items[j]->getPosition().col == player->getPosition().col + c[i]) {
              if (!items[j]->isGuarded()) {
                moved = true;
                player->setPosition(Posn{player->getPosition().row + r[i],
                                         player->getPosition().col + c[i]});
                player->addGold(items[j]->getValue());
                msg = "You moved " + directions[i] + " and picked up " +
                      to_string(items[j]->getValue()) + " gold. ";
                displayGrid[items[j]->getPosition().row][items[j]->getPosition().col] = '.';
                items.erase(remove(items.begin(), items.end(), items[j]), items.end());
                break;
              }
            }
          }
          break;
        } else if (tmp == 'C') {
          moved = true;
          player->setPosition(Posn{player->getPosition().row + r[i],
                                   player->getPosition().col + c[i]});
          stairVisible = true;
          for (auto it : items) {
            if (it->getPosition() == player->getPosition()) {
              items.erase(remove(items.begin(), items.end(), it), items.end());
              break;
            }
          }
          msg = "You moved " + directions[i] + " and picked up the compass. ";
          break;
        } else if (tmp == 'B') {
          for (int j = 0; j < items.size(); j++) {
            if (items[j]->getPosition().row == player->getPosition().row + r[i] &&
                items[j]->getPosition().col == player->getPosition().col + c[i]) {
              if (!items[j]->isGuarded()) {
                moved = true;
                player->setPosition(Posn{player->getPosition().row + r[i],
                                         player->getPosition().col + c[i]});
                player->toggleBarrier();
                msg = "You moved " + directions[i] + " and picked up the barrier. ";
                displayGrid[items[j]->getPosition().row][items[j]->getPosition().col] = '.';
                items.erase(remove(items.begin(), items.end(), items[j]), items.end());
                break;
              }
            }
          }
        }
      }
    }
    if (input == "a") {
      string di;
      cin >> di;
      for (int i = 0; i < 8; i++) {
        if (di == movement[i]) {
          Posn enemypos = Posn{player->getPosition().row + r[i],
                               player->getPosition().col + c[i]};
          for (auto en : enemies) {
            if (enemypos == en->getPosition()) {
              int oldHP = en->getHP();
              player->attack(en);
              int damage = oldHP - en->getHP();
              msg = "PC deals " + to_string(damage) + " damage to " +
                    en->getSymbol() + " (" + to_string(max(0, en->getHP())) + " HP). ";
              moved = true;
              if (en->getSymbol() == 'M') {
                en->setHostile();
              }
              break;
            }
          }
        }
      }
    }
    if (input == "u") {
      string di;
      cin >> di;
      for (int i = 0; i < 8; i++) {
        if (di == movement[i]) {
          Posn potionpos = Posn{player->getPosition().row + r[i],
                                player->getPosition().col + c[i]};
          for (auto it : items) {
            if (potionpos == it->getPosition() && it->getSymbol() == 'P') {
              if (it->getId() == 0 || it->getId() == 3) {
                player->addHealth(it->getValue());
                if (it->getId() == 0) {
                  msg = "PC picked up a RH potion. ";
                } else {
                  msg = "PC picked up a PH potion. ";
                }
              }
              if (it->getId() == 1) {
                player = new AtkBuff(player, "BA");
                msg = "PC picked up a BA potion. ";
              }
              if (it->getId() == 2) {
                player = new DefBuff(player, "BD");
                msg = "PC picked up a BD potion. ";
              }
              if (it->getId() == 4) {
                player = new AtkBuff(player, "WA");
                msg = "PC picked up a WA potion. ";
              }
              if (it->getId() == 5) {
                player = new DefBuff(player, "WD");
                msg = "PC picked up a WD potion. ";
              }
              player->toggleknownPotions(it->getId());
              displayGrid[it->getPosition().row][it->getPosition().col] = '.';
              items.erase(remove(items.begin(), items.end(), it), items.end());
              moved = true;
              cout << it->getId() << endl;
              break;
            }
          }
        }
      }
    }
    if (input == "r") {
      restart();
      moved = true;
      msg = "You have restarted the game. Welcome to the dungeon!";
    }
    if (input == "q") {
      break;
    }
    if (!moved) {
      cout << "Invalid move. " << endl;
      continue;
    }
    if (!newLevel) {
      msg = msg + update();
    } else {
      newLevel = false;
    }
    print();
    cout << msg << endl;
    if (player->getHP() <= 0) {
      cout << "You died :( Press [r] to play again. " << endl;
      continue;
    }
  }
}

string Game::update() {
  string msg = "";
  // displayGrid = defaultMap;
  for (auto en : enemies) {
    bool moved = false;
    bool attacked = false;
    if (en->getHP() <= 0) {
      if (en->getSymbol() == 'M') {
        items.emplace_back(new Gold(8, en->getPosition()));
        msg = "You killed the merchant and found a merchant hoard. ";
        displayGrid[en->getPosition().row][en->getPosition().col] = 'G';
      } else {
        player->addGold(en->getGold());
        msg = msg + "You slained " + (en->getSymbol()) + " and got " +
              to_string(en->getGold()) + " gold. ";
        displayGrid[en->getPosition().row][en->getPosition().col] = '.';
      }
      if (en->compass) {
        items.emplace_back(new Compass(en->getPosition()));
      }
      if (en->getSymbol() == 'D') {
        en->getItem()->setGuarded(false);
      }
      enemies.erase(remove(enemies.begin(), enemies.end(), en), enemies.end());
      continue;
    }
    for (int i = 0; i < 8; i++) {
      Posn enemyattack =
          Posn{en->getPosition().row + r[i], en->getPosition().col + c[i]};
      if (enemyattack == player->getPosition()) {
        if (en->getSymbol() == 'D') {
          for (int j = 0; j < 8; j++) {
            if (en->getItem()->getPosition().row == player->getPosition().row + r[j] &&
                en->getItem()->getPosition().col == player->getPosition().col + c[j]) {
              int hit = randomNum(2);
              if (hit == 1) {
                int oldHP = player->getHP();
                en->attack(player);
                if (oldHP != player->getHP()) {
                  int damage = oldHP - player->getHP();
                  msg = msg + en->getSymbol() + " deals " + to_string(damage) + " damage to PC. ";
                }
              } else {
                msg = msg + en->getSymbol() + " missed. ";
              }
              attacked = true;
            }
          }
        } else if (en->getSymbol() == 'M') {
          if (en->isHostile()) {
            int hit = randomNum(2);
            if (hit == 1) {
              int oldHP = player->getHP();
              en->attack(player);
              if (oldHP != player->getHP()) {
                int damage = oldHP - player->getHP();
                msg = msg + en->getSymbol() + " deals " + to_string(damage) + " damage to PC. ";
              }
            } else {
              msg = msg + en->getSymbol() + " missed. ";
            }
            attacked = true;
          }
        } else {
          int hit = randomNum(2);
          if (hit == 1) {
            int oldHP = player->getHP();
            en->attack(player);
            if (oldHP != player->getHP()) {
              int damage = oldHP - player->getHP();
              msg = msg + en->getSymbol() + " deals " + to_string(damage) + " damage to PC. ";
            }
          } else {
            msg = msg + en->getSymbol() + " missed. ";
          }
          attacked = true;
        }
      }
    }
    if (attacked) {
      continue;
    }
    bool canMove = false;
    for (int i = 0; i < 8; i++) {
      Posn enemypos = Posn{en->getPosition().row + r[i],
                           en->getPosition().col + c[i]};
      if (displayGrid[enemypos.row][enemypos.col] == '.') {
        canMove = true;
        break;
      }
    }
    if (canMove) {
      int di = randomNum(8);
      while (!moved) {
        if (displayGrid[en->getPosition().row + r[di]][en->getPosition().col + c[di]] == '.') {
          if (en->getSymbol() == 'D') {
            bool correctMovement = false;
            for (int i = 0; i < 8; i++) {
              if (en->getItem()->getPosition().row + r[i] == en->getPosition().row + r[di] &&
                  en->getItem()->getPosition().col + c[i] == en->getPosition().col + c[di]) {
                correctMovement = true;
                break;
              }
            }
            if (correctMovement) {
              displayGrid[en->getPosition().row][en->getPosition().col] = '.';
              en->setPosition(Posn{en->getPosition().row + r[di], en->getPosition().col + c[di]});
              displayGrid[en->getPosition().row][en->getPosition().col] = en->getSymbol();
              moved = true;
            } else {
              moved = true;
            }
          } else {
            displayGrid[en->getPosition().row][en->getPosition().col] = '.';
            en->setPosition(Posn{en->getPosition().row + r[di], en->getPosition().col + c[di]});
            displayGrid[en->getPosition().row][en->getPosition().col] = en->getSymbol();
            moved = true;
          }
        } else {
          di = randomNum(8);
        }
      }
    }
  }
  for (int i = 0; i < 8; i++) {
    if (displayGrid[player->getPosition().row + r[i]][player->getPosition().col + c[i]] == 'P') {
      for (auto it : items) {
        if (it->getPosition().row == player->getPosition().row + r[i] &&
            it->getPosition().col == player->getPosition().col + c[i] && it->getSymbol() == 'P') {
          if (player->getknownPotions(it->getId())) {
            msg = msg + "PC sees a ";
            if (it->getId() == 0) {
              msg = msg + "RH potion. ";
            } else if (it->getId() == 1) {
              msg = msg + "BA potion. ";
            } else if (it->getId() == 2) {
              msg = msg + "BD potion. ";
            } else if (it->getId() == 3) {
              msg = msg + "PH potion. ";
            } else if (it->getId() == 4) {
              msg = msg + "WA potion. ";
            } else if (it->getId() == 5) {
              msg = msg + "WD potion. ";
            }
          } else {
            msg = msg + "PC sees an unknown potion. ";
          }
        }
      }
    }
  }
  displayGrid = defaultMap;
  displayGrid[player->getPosition().row][player->getPosition().col] = '@';
  for (auto en : enemies) {
    displayGrid[en->getPosition().row][en->getPosition().col] = en->getSymbol();
  }
  for (auto it : items) {
    displayGrid[it->getPosition().row][it->getPosition().col] = it->getSymbol();
  }
  if (stairVisible) {
    displayGrid[getStairs().row][getStairs().col] = '\\';
  }
  return msg;
}

void Game::generatePlayer(char symbol) {
  int chamber = randomNum(5) + 1;
  Posn posn = randomPosn(chamber);
  if (playerSymbol == 'h') {
    player = new Human(posn);
  } else if (playerSymbol == 'd') {
    player = new Dwarf(posn);
  } else if (playerSymbol == 'e') {
    player = new Elf(posn);
  } /*else {
      player = new Orc(posn);
  }*/
  displayGrid[posn.row][posn.col] = '@';
}

bool Game::neighborHasPlayer(Posn posn) {
  for (int i = 0; i < 8; i++) {
    if (displayGrid[posn.row + r[i]][posn.col + c[i]] == '@') {
      return true;
    }
  }
  return false;
}

void Game::generateEnemies() {
  int numEnemies = 20 - enemies.size();
  for (int i = 0; i < numEnemies; i++) {
    int chamber = randomNum(5) + 1;
    Posn posn = randomPosn(chamber);
    while (neighborHasPlayer(posn)) {
      posn = randomPosn(chamber);
    }
    int type = randomNum(18);  // 0 - 3 Werewolf, 4 - 6 Vampire, 7 - 11 Goblin, 12 - 13 Troll,
    if (type < 4) {            // 14 - 15 Pheonix, 16 - 17 Merchant
      enemies.push_back(new Werewolf(posn));
      displayGrid[posn.row][posn.col] = 'W';
    } else if (type < 7) {
      enemies.push_back(new Vampire(posn));
      displayGrid[posn.row][posn.col] = 'V';
    } else if (type < 12) {
      enemies.push_back(new Goblin(posn));
      displayGrid[posn.row][posn.col] = 'N';
    } else if (type < 14) {
      enemies.push_back(new Troll(posn));
      displayGrid[posn.row][posn.col] = 'T';
    } else if (type < 16) {
      enemies.push_back(new Phoenix(posn));
      displayGrid[posn.row][posn.col] = 'X';
    } else {
      enemies.push_back(new Merchant(posn));
      displayGrid[posn.row][posn.col] = 'M';
    }
  }
  int compassHolder = randomNum(20);
  enemies[compassHolder]->compass = true;
}

void Game::nextLevel() {
  level++;
  for (int i = 0; i < enemies.size(); i++) {
    delete enemies[i];
  }
  enemies.clear();
  for (int i = 0; i < items.size(); i++) {
    delete items[i];
  }
  items.clear();
  displayGrid = defaultMap;
  stairVisible = false;
  int HP = player->getHP();
  int Gold = player->getGold();
  bool hasBarrier = player->hasBarrier();
  bool KnownPotions[6] = {player->getknownPotions(0), player->getknownPotions(1), player->getknownPotions(2),
                          player->getknownPotions(3), player->getknownPotions(4), player->getknownPotions(5)};
  delete player;
  init();
  player->setHP(HP);
  player->setGold(Gold);
  for (int i = 0; i < 6; i++) {
    if (KnownPotions[i]) {
      player->toggleknownPotions(i);
    }
  }
  if (hasBarrier) {
    player->toggleBarrier();
  }
}

int Game::getLevel() { return level; }

Player *Game::getPlayer() { return player; }

Posn Game::getStairs() { return stairPosition; }

void Game::print() {
  for (int i = 0; i < 25; i++) {
    for (int j = 0; j < 79; j++) {
      cout << displayGrid[i][j];
    }
    cout << endl;
  }
  cout << "Race: " << player->getRace() << " Gold: " << player->getGold()
       << "\t\t\t\t\t\tFloor: " << level << endl;
  cout << "HP: " << max(0, player->getHP()) << endl;
  cout << "Atk: " << player->getAtk() << endl;
  cout << "Def: " << player->getDef() << endl;
  cout << "Action: ";
}

Game::~Game() {
  for (int i = 0; i < enemies.size(); i++) {
    delete enemies[i];
  }
  for (int i = 0; i < items.size(); i++) {
    delete items[i];
  }
  delete player;
}

void Game::generateItems() {
  int numPotions = 10;
  for (int i = 0; i < numPotions; i++) {
    int chamber = randomNum(5) + 1;
    Posn posn = randomPosn(chamber);
    while (neighborHasPlayer(posn)) {
      posn = randomPosn(chamber);
    }
    int type = randomNum(6);  // 0 - RH, 1 - BA, 2 - BD, 3 - PH, 4 - WA, 5 - WD
    items.emplace_back(new Potion(type, posn));
    displayGrid[posn.row][posn.col] = 'P';
  }
  int numGolds = 10;
  for (int i = 0; i < numGolds; i++) {
    int chamber = randomNum(5) + 1;
    Posn posn = randomPosn(chamber);
    while (neighborHasPlayer(posn)) {
      posn = randomPosn(chamber);
    }
    int type = randomNum(8);  // 0-4 normal gold,  5-6 small hoard, 7 dragon hoard
    if (type <= 4) {
      items.emplace_back(new Gold(6, posn));
    } else if (type <= 6) {
      items.emplace_back(new Gold(7, posn));
    } else {
      Item *item = new DragonHoard(posn);
      items.emplace_back(item);
      // random posn for dragon
      Posn dragonPosn = randomNeighbour(posn);
      enemies.push_back(new Dragon(dragonPosn, item));
      displayGrid[dragonPosn.row][dragonPosn.col] = 'D';
    }
    displayGrid[posn.row][posn.col] = 'G';
  }
  if (getLevel() == barrierFloor) {
    int chamber = randomNum(5) + 1;
    Posn posn = randomPosn(chamber);
    while (neighborHasPlayer(posn)) {
      posn = randomPosn(chamber);
    }
    BarrierSuit *bar = new BarrierSuit(posn);
    items.emplace_back(bar);
    displayGrid[posn.row][posn.col] = 'B';
    Posn dragonPosn = randomNeighbour(posn);
    enemies.push_back(new Dragon(dragonPosn, bar));
    displayGrid[dragonPosn.row][dragonPosn.col] = 'D';
  }
}

void Game::restart() {
  for (int i = 0; i < enemies.size(); i++) {
    delete enemies[i];
  }
  enemies.clear();
  for (int i = 0; i < items.size(); i++) {
    delete items[i];
  }
  items.clear();
  delete player;
  cout << "Welcome to CC3K!" << endl;
  cout << "Please choose your character:" << endl;
  cout << "Human (h)" << endl;
  cout << "Dwarf (d)" << endl;
  cout << "Elf (e)" << endl;
  cout << "Orc (o)" << endl;
  char Symbol;
  cin >> Symbol;
  while (Symbol != 'h' && Symbol != 'd' && Symbol != 'e' && Symbol != 'o') {
    cout << "Invalid character. Please try again." << endl;
    cin >> Symbol;
  }
  playerSymbol = Symbol;
  displayGrid = defaultMap;
  level = 1;
  stairVisible = false;
  barrierFloor = randomNum(5) + 1;
  init();
}