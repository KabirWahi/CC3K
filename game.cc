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
const string directions[8] = {"North", "South", "East",
                              "West", "Northeast", "Northwest",
                              "Southeast", "Southwest"};

void Game::changeMap(string filename) {
  ifstream file(filename);
  vector<string> map;
  string line;
  while (getline(file, line)) {
    map.push_back(line);
  }
  height = map.size();
  width = map[0].size();
  for (int i = 0; i < height; i++) {
    defaultMap.push_back(vector<char>());
    for (int j = 0; j < width; j++) {
      defaultMap[i].push_back(map[i][j]);
    }
  }
  displayGrid = defaultMap;
  file.close();
  mapPosns = mapDetection(map);
  chamberCount = mapPosns.size();
}

Game::Game(char playerSymbol, bool bonus) : bonus{bonus}, playerSymbol(playerSymbol), level(1), stairVisible(false), barrierFloor{randomNum(5) + 1} {}

void Game::init() {
  for (size_t i = 0; i < defaultMap.size(); i++) {
    for (size_t j = 0; j < defaultMap[i].size(); j++) {
      if ('0' <= defaultMap[i][j] && defaultMap[i][j] <= '5') {
        items.emplace_back(new Potion(defaultMap[i][j] - '0', Posn{int(i), int(j)}));
        defaultMap[i][j] = '.';
        displayGrid[i][j] = 'P';
      } else if ('6' <= defaultMap[i][j] && defaultMap[i][j] <= '8') {
        items.emplace_back(new Gold(defaultMap[i][j] - '0', Posn{int(i), int(j)}));
        defaultMap[i][j] = '.';
        displayGrid[i][j] = 'G';
      } else if (defaultMap[i][j] == '9') {
        Posn posn = Posn{int(i), int(j)};
        Item *item = new DragonHoard(posn);
        items.emplace_back(item);
        Posn dragonPosn = randomNeighbour(posn);
        enemies.push_back(new Dragon(dragonPosn, item));
        defaultMap[i][j] = '.';
        displayGrid[i][j] = 'G';
        displayGrid[dragonPosn.getRow()][dragonPosn.getCol()] = 'D';
      }
    }
  }
  generatePlayer(playerSymbol);
  int chamber = randomNum(chamberCount) + 1;
  while (chamber == playerStartChamber) {
    chamber = randomNum(chamberCount) + 1;
  }
  stairPosition = randomPosn(chamber);
  displayGrid[stairPosition.getRow()][stairPosition.getCol()] = '\\';
  if (items.empty()) {
    generateItems();
  }
  generateEnemies();
  displayGrid[stairPosition.getRow()][stairPosition.getCol()] = '.';
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
  int row = posn.getRow();
  int col = posn.getCol();
  int neighbour = randomNum(8);
  row += r[neighbour];
  col += c[neighbour];
  while (displayGrid[row][col] != '.') {
    row = posn.getRow();
    col = posn.getCol();
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
        char tmp = displayGrid[player->getPosition().getRow() + r[i]]
                              [player->getPosition().getCol() + c[i]];
        if (tmp == '.' || tmp == '+' || tmp == '#' || tmp == '\\') {
          moved = true;
          player->setPosition(Posn{player->getPosition().getRow() + r[i],
                                   player->getPosition().getCol() + c[i]});
          displayGrid[player->getPosition().getRow()][player->getPosition().getCol()] = '@';
          if (player->getPosition() == stairPosition) {
            if (level == 5) {
              cout << "Congratulations! You have reached the end of the dungeon." << endl;
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
          for (auto it : items) {
            if (it->getPosition().getRow() == player->getPosition().getRow() + r[i] &&
                it->getPosition().getCol() == player->getPosition().getCol() + c[i]) {
              if (!it->isGuarded()) {
                moved = true;
                player->setPosition(Posn{player->getPosition().getRow() + r[i],
                                         player->getPosition().getCol() + c[i]});
                player->addGold(it->getValue());
                msg = "You moved " + directions[i] + " and picked up " +
                      to_string(it->getValue()) + " gold. ";
                displayGrid[it->getPosition().getRow()][it->getPosition().getCol()] = '.';
                Item *temp = it;
                items.erase(remove(items.begin(), items.end(), it), items.end());
                delete temp;
                break;
              }
            }
          }
          break;
        } else if (tmp == 'C') {
          moved = true;
          player->setPosition(Posn{player->getPosition().getRow() + r[i],
                                   player->getPosition().getCol() + c[i]});
          stairVisible = true;
          for (auto it : items) {
            if (it->getPosition() == player->getPosition()) {
              Item *temp = it;
              items.erase(remove(items.begin(), items.end(), it), items.end());
              delete temp;
              break;
            }
          }
          msg = "You moved " + directions[i] + " and picked up the compass. ";
          break;
        } else if (tmp == 'B') {
          for (auto it : items) {
            if (it->getPosition().getRow() == player->getPosition().getRow() + r[i] &&
                it->getPosition().getCol() == player->getPosition().getCol() + c[i]) {
              if (!it->isGuarded()) {
                moved = true;
                player->setPosition(Posn{player->getPosition().getRow() + r[i],
                                         player->getPosition().getCol() + c[i]});
                player->toggleBarrier();
                msg = "You moved " + directions[i] + " and picked up the barrier. ";
                displayGrid[it->getPosition().getRow()][it->getPosition().getCol()] = '.';
                Item *temp = it;
                items.erase(remove(items.begin(), items.end(), it), items.end());
                delete temp;
                break;
              }
            }
          }
        } else if (tmp == 'K') {
          for (auto it : items) {
            if (it->getPosition().getRow() == player->getPosition().getRow() + r[i] &&
                it->getPosition().getCol() == player->getPosition().getCol() + c[i]) {
              if (!it->isGuarded()) {
                moved = true;
                player->setPosition(Posn{player->getPosition().getRow() + r[i],
                                         player->getPosition().getCol() + c[i]});
                for (int k = 0; k < 6; k++) {
                  player->toggleknownPotions(k);
                }
                msg = "You moved " + directions[i] + " and picked up the Potion Book. ";
                displayGrid[it->getPosition().getRow()][it->getPosition().getCol()] = '.';
                Item *temp = it;
                items.erase(remove(items.begin(), items.end(), it), items.end());
                delete temp;
                break;
              }
            }
          }
        }
      }
    }
    if (input == "a") {
      msg = "";
      // bonus Valkyrie and Magic Archer
      if (bonus) {
        if (playerSymbol == 'g') {
          moved = true;
          for (auto en : enemies) {
            player->attack(en);
          }
          msg = "You slained every enemy on the floor. ";
        } else if (playerSymbol == 'm') {
          string di;
          cin >> di;
          for (int i = 0; i < 8; i++) {
            if (di == movement[i]) {
              moved = true;
              Posn enemypos = Posn{player->getPosition().getRow() + r[i],
                                   player->getPosition().getCol() + c[i]};
              while (displayGrid[enemypos.getRow()][enemypos.getCol()] != '-' &&
                     displayGrid[enemypos.getRow()][enemypos.getCol()] != '|' &&
                     displayGrid[enemypos.getRow()][enemypos.getCol()] != '+' &&
                     displayGrid[enemypos.getRow()][enemypos.getCol()] != '#') {
                if (displayGrid[enemypos.getRow()][enemypos.getCol()] != '.' &&
                    displayGrid[enemypos.getRow()][enemypos.getCol()] != 'G' &&
                    displayGrid[enemypos.getRow()][enemypos.getCol()] != 'P') {
                  for (auto en : enemies) {
                    if (en->getPosition() == enemypos) {
                      msg = msg + player->attack(en);
                      break;
                    }
                  }
                }
                enemypos = Posn{enemypos.getRow() + r[i], enemypos.getCol() + c[i]};
              }
            }
          }
        } else if (playerSymbol == 'v') {
          moved = true;
          for (int i = 0; i < 8; i++) {
            Posn enemypos = Posn{player->getPosition().getRow() + r[i],
                                 player->getPosition().getCol() + c[i]};
            for (auto en : enemies) {
              if (en->getPosition() == enemypos) {
                msg = msg + player->attack(en);
                break;
              }
            }
          }
        }
      } else {
        string di;
        cin >> di;
        for (int i = 0; i < 8; i++) {
          if (di == movement[i]) {
            Posn enemypos = Posn{player->getPosition().getRow() + r[i],
                                 player->getPosition().getCol() + c[i]};
            for (auto en : enemies) {
              if (enemypos == en->getPosition()) {
                msg = player->attack(en);
                moved = true;
                break;
              }
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
          Posn potionpos = Posn{player->getPosition().getRow() + r[i],
                                player->getPosition().getCol() + c[i]};
          for (auto it : items) {
            if (potionpos == it->getPosition() && it->getSymbol() == 'P') {
              moved = true;
              msg = player->usePotion(it);
              if (it->getId() == 1 || it->getId() == 4) {
                player = new AtkBuff(player, it->getName());
              }
              if (it->getId() == 2 || it->getId() == 5) {
                player = new DefBuff(player, it->getName());
              }
              player->toggleknownPotions(it->getId());
              displayGrid[it->getPosition().getRow()][it->getPosition().getCol()] = '.';
              Item *temp = it;
              items.erase(remove(items.begin(), items.end(), it), items.end());
              delete temp;
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
      const std::string BOLD = "\033[1m";
      const std::string RESET = "\033[0m";
      cout << BOLD << "You died :( Your score is " << player->getGold() << ". " << RESET << endl;
      break;
    }
  }
}

string Game::update() {
  string msg = "";
  // displayGrid = defaultMap;
  for (auto en = enemies.begin(); en != enemies.end();) {
    if ((*en)->getHP() <= 0) {
      if ((*en)->getSymbol() == 'M') {
        items.emplace_back(new Gold(8, (*en)->getPosition()));
        msg = msg + "You killed the merchant and found a merchant hoard. ";
        displayGrid[(*en)->getPosition().getRow()][(*en)->getPosition().getCol()] = 'G';
      } else {
        player->addGold((*en)->getGold());
        msg = msg + "You slained " + ((*en)->getSymbol()) + " and got " +
              to_string((*en)->getGold()) + " gold. ";
        displayGrid[(*en)->getPosition().getRow()][(*en)->getPosition().getCol()] = '.';
      }
      if ((*en)->compass) {
        items.emplace_back(new Compass((*en)->getPosition()));
      }
      if ((*en)->getSymbol() == 'D') {
        (*en)->getItem()->setGuarded(false);
      }
      Enemy *temp = *en;
      enemies.erase(en);
      delete temp;
    } else {
      en++;
    }
  }
  for (auto en : enemies) {
    bool moved = false;
    bool attacked = false;
    for (int i = 0; i < 8; i++) {
      Posn enemyattack = Posn{en->getPosition().getRow() + r[i], en->getPosition().getCol() + c[i]};
      if (enemyattack == player->getPosition()) {
        msg = msg + en->attack(player);
        attacked = true;
        break;
      }
    }
    if (attacked) {
      continue;
    }
    bool canMove = false;
    for (int i = 0; i < 8; i++) {
      Posn enemypos = Posn{en->getPosition().getRow() + r[i],
                           en->getPosition().getCol() + c[i]};
      if (displayGrid[enemypos.getRow()][enemypos.getCol()] == '.') {
        canMove = true;
        break;
      }
    }
    if (canMove) {
      int di = randomNum(8);
      while (!moved) {
        if (displayGrid[en->getPosition().getRow() + r[di]][en->getPosition().getCol() + c[di]] == '.') {
          if (en->getSymbol() == 'D') {
            bool correctMovement = false;
            for (int i = 0; i < 8; i++) {
              for (int j = 0; j < 8; j++) {
                if (en->getItem()->getPosition().getRow() + r[i] == en->getPosition().getRow() + r[j] &&
                    en->getItem()->getPosition().getCol() + c[i] == en->getPosition().getCol() + c[j] &&
                    displayGrid[en->getPosition().getRow() + r[j]][en->getPosition().getCol() + c[j]] == '.') {
                correctMovement = true;
                break;
              }
              }
            }
            if (correctMovement) {
              while (!moved) {
                di = randomNum(8);
                if (displayGrid[en->getPosition().getRow() + r[di]][en->getPosition().getCol() + c[di]] == '.') {
                  for (int i = 0; i < 8; i++) {
                    if (en->getItem()->getPosition().getRow() + r[i] == en->getPosition().getRow() + r[di] &&
                        en->getItem()->getPosition().getCol() + c[i] == en->getPosition().getCol() + c[di]) {
                      moved = true;
                      displayGrid[en->getPosition().getRow()][en->getPosition().getCol()] = '.';
                      en->setPosition(Posn{en->getPosition().getRow() + r[di], en->getPosition().getCol() + c[di]});
                      displayGrid[en->getPosition().getRow()][en->getPosition().getCol()] = en->getSymbol();
                      break;
                    }
                  }
                }
              }
            } else {
              moved = true;
            }
          } else {
            displayGrid[en->getPosition().getRow()][en->getPosition().getCol()] = '.';
            en->setPosition(Posn{en->getPosition().getRow() + r[di], en->getPosition().getCol() + c[di]});
            displayGrid[en->getPosition().getRow()][en->getPosition().getCol()] = en->getSymbol();
            moved = true;
          }
        } else {
          di = randomNum(8);
        }
      }
    }
    en++;
  }
  for (int i = 0; i < 8; i++) {
    if (displayGrid[player->getPosition().getRow() + r[i]][player->getPosition().getCol() + c[i]] == 'P') {
      for (auto it : items) {
        if (it->getPosition().getRow() == player->getPosition().getRow() + r[i] &&
            it->getPosition().getCol() == player->getPosition().getCol() + c[i] && it->getSymbol() == 'P') {
          if (player->getknownPotions(it->getId())) {
            msg = msg + "PC sees a " + it->getName() + " potion. ";
          } else {
            msg = msg + "PC sees an unknown potion. ";
          }
        }
      }
    }
  }
  displayGrid = defaultMap;
  displayGrid[player->getPosition().getRow()][player->getPosition().getCol()] = '@';
  for (auto en : enemies) {
    displayGrid[en->getPosition().getRow()][en->getPosition().getCol()] = en->getSymbol();
  }
  for (auto it : items) {
    displayGrid[it->getPosition().getRow()][it->getPosition().getCol()] = it->getSymbol();
  }
  if (stairVisible) {
    displayGrid[getStairs().getRow()][getStairs().getCol()] = '\\';
  }
  return msg;
}

void Game::generatePlayer(char symbol) {
  int chamber = randomNum(chamberCount) + 1;
  playerStartChamber = chamber;
  Posn posn = randomPosn(chamber);
  if (playerSymbol == 'h') {
    player = new Human(posn);
  } else if (playerSymbol == 'd') {
    player = new Dwarf(posn);
  } else if (playerSymbol == 'e') {
    player = new Elf(posn);
  } else if (playerSymbol == 'o') {
    player = new Orc(posn);
  } else if (playerSymbol == 'g') {
    player = new God(posn);
  } else if (playerSymbol == 'm') {
    player = new MagicArcher(posn);
  } else if (playerSymbol == 'v') {
    player = new Valkyrie(posn);
  }
  displayGrid[posn.getRow()][posn.getCol()] = '@';
}

bool Game::neighborHasPlayer(Posn posn) {
  for (int i = 0; i < 8; i++) {
    if (displayGrid[posn.getRow() + r[i]][posn.getCol() + c[i]] == '@') {
      return true;
    }
  }
  return false;
}

void Game::generateEnemies() {
  int numEnemies = 20 - enemies.size();
  for (int i = 0; i < numEnemies; i++) {
    int chamber = randomNum(chamberCount) + 1;
    Posn posn = randomPosn(chamber);
    while (neighborHasPlayer(posn)) {
      posn = randomPosn(chamber);
    }
    int type;
    if (bonus) {
      type = randomNum(20);
    } else {
      type = randomNum(18);   // 0 - 3 Werewolf, 4 - 6 Vampire, 7 - 11 Goblin, 12 - 13 Troll,
    }                              // 14 - 15 Pheonix, 16 - 17 Merchant, 18 - 19 Ditto
    if (type < 4) {            
      enemies.push_back(new Werewolf(posn));
      displayGrid[posn.getRow()][posn.getCol()] = 'W';
    } else if (type < 7) {
      enemies.push_back(new Vampire(posn, bonus));
      displayGrid[posn.getRow()][posn.getCol()] = 'V';
    } else if (type < 12) {
      enemies.push_back(new Goblin(posn, bonus));
      displayGrid[posn.getRow()][posn.getCol()] = 'N';
    } else if (type < 14) {
      enemies.push_back(new Troll(posn, bonus));
      displayGrid[posn.getRow()][posn.getCol()] = 'T';
    } else if (type < 16) {
      enemies.push_back(new Phoenix(posn));
      displayGrid[posn.getRow()][posn.getCol()] = 'X';
    } else if (type < 18) {
      enemies.push_back(new Merchant(posn));
      displayGrid[posn.getRow()][posn.getCol()] = 'M';
    } else {
      enemies.push_back(new Reverser(posn));
      displayGrid[posn.getRow()][posn.getCol()] = 'R';
    }
  }
  int compassHolder = randomNum(20);
  enemies[compassHolder]->compass = true;
}

void Game::nextLevel() {
  level++;
  for (auto i : enemies) {
    delete i;
  }
  enemies.clear();
  for (auto i : items) {
    delete i;
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
  const std::string GREEN = "\033[1;32m";
  const std::string RED = "\033[1;31m";
  const std::string BLUE = "\033[1;34m";
  const std::string PURPLE = "\033[1;35m";
  const std::string CYAN = "\033[1;36m";
  const std::string GOLDEN = "\033[1;33m";
  const std::string RESET = "\033[0m";
  const std::string BOLD = "\033[1m";

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      if (displayGrid[i][j] == '@' || displayGrid[i][j] == '\\') {
        cout << GREEN << displayGrid[i][j] << RESET;
      } else if (displayGrid[i][j] == 'W' || displayGrid[i][j] == 'V' || displayGrid[i][j] == 'N' ||
                 displayGrid[i][j] == 'T' || displayGrid[i][j] == 'X' || displayGrid[i][j] == 'M' || displayGrid[i][j] == 'D' || displayGrid[i][j] == 'R') {
        cout << RED << displayGrid[i][j] << RESET;
      } else if (displayGrid[i][j] == '#' || displayGrid[i][j] == '+' || displayGrid[i][j] == '|' || displayGrid[i][j] == '-') {
        cout << BLUE << displayGrid[i][j] << RESET;
      } else if (displayGrid[i][j] == 'G' || displayGrid[i][j] == 'C' || displayGrid[i][j] == 'B' || displayGrid[i][j] == 'K') {
        cout << GOLDEN << displayGrid[i][j] << RESET;
      } else if (displayGrid[i][j] == 'P') {
        cout << PURPLE << displayGrid[i][j] << RESET;
      } else if (displayGrid[i][j] == '.') {
        cout << CYAN << displayGrid[i][j] << RESET;
      } else {
        cout << displayGrid[i][j];
      }
    }
    cout << endl;
  }
  cout << BOLD << "Race: " << RESET << player->getRace();
  cout << BOLD << " Gold: " << RESET << player->getGold();
  cout << BOLD << "\t\t\t\t\t\tFloor: " << RESET << level << endl;
  cout << BOLD << "HP: " << RESET << max(0, player->getHP()) << endl;
  cout << BOLD << "Atk: " << RESET << player->getAtk() << endl;
  cout << BOLD << "Def: " << RESET << player->getDef() << endl;
  cout << BOLD << "Action: " << RESET;
}

Game::~Game() {
  for (auto i : enemies) {
    delete i;
  }
  for (auto i : items) {
    delete i;
  }
  delete player;
  for (size_t i = 0; i < defaultMap.size(); i++) {
    defaultMap[i].clear();
    displayGrid[i].clear();
  }
  defaultMap.clear();
  displayGrid.clear();
}

void Game::generateItems() {
  int numPotions = 10;
  for (int i = 0; i < numPotions; i++) {
    int chamber = randomNum(chamberCount) + 1;
    Posn posn = randomPosn(chamber);
    while (neighborHasPlayer(posn)) {
      posn = randomPosn(chamber);
    }
    int type = randomNum(6);  // 0 - RH, 1 - BA, 2 - BD, 3 - PH, 4 - WA, 5 - WD
    items.emplace_back(new Potion(type, posn));
    displayGrid[posn.getRow()][posn.getCol()] = 'P';
  }
  int numGolds = 10;
  for (int i = 0; i < numGolds; i++) {
    int chamber = randomNum(chamberCount) + 1;
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
      displayGrid[dragonPosn.getRow()][dragonPosn.getCol()] = 'D';
    }
    displayGrid[posn.getRow()][posn.getCol()] = 'G';
  }
  if (getLevel() == barrierFloor) {
    int chamber = randomNum(chamberCount) + 1;
    Posn posn = randomPosn(chamber);
    while (neighborHasPlayer(posn)) {
      posn = randomPosn(chamber);
    }
    BarrierSuit *bar = new BarrierSuit(posn);
    items.emplace_back(bar);
    displayGrid[posn.getRow()][posn.getCol()] = 'B';
    Posn dragonPosn = randomNeighbour(posn);
    enemies.push_back(new Dragon(dragonPosn, bar));
    displayGrid[dragonPosn.getRow()][dragonPosn.getCol()] = 'D';
  }
  if (level == 1 && bonus) {
    int chamber = randomNum(chamberCount) + 1;
    Posn posn = randomPosn(chamber);
    while (neighborHasPlayer(posn)) {
      posn = randomPosn(chamber);
    }
    PotionBook *pb = new PotionBook(posn);
    items.emplace_back(pb);
    displayGrid[posn.getRow()][posn.getCol()] = 'K';
    Posn dragonPosn = randomNeighbour(posn);
    enemies.push_back(new Dragon(dragonPosn, pb));
    displayGrid[dragonPosn.getRow()][dragonPosn.getCol()] = 'D';
  }
}

void Game::restart() {
  for (auto i : enemies) {
    delete i;
  }
  enemies.clear();
  for (auto i : items) {
    delete i;
  }
  items.clear();
  delete player;
  const std::string BOLD = "\033[1m";
  const std::string RESET = "\033[0m";
  cout << BOLD;
  cout << "Welcome to CC3K!" << endl;
  cout << "Please choose your character:" << endl;
  cout << "Human (h)" << endl;
  cout << "Dwarf (d)" << endl;
  cout << "Elf (e)" << endl;
  cout << "Orc (o)" << endl;
  if (bonus) {
    cout << "God (g)" << endl;
    cout << "Magic Archer (m)" << endl;
    cout << "Valkyrie (v)" << endl;
  }
  char Symbol;
  cin >> Symbol;
  if (bonus) {
    while (playerSymbol != 'h' && playerSymbol != 'd' && playerSymbol != 'e' &&
           playerSymbol != 'o' && playerSymbol != 'q' && playerSymbol != 'g' &&
           playerSymbol != 'v' && playerSymbol != 'm') {
      cout << "Invalid character. Please try again." << endl;
      cin >> playerSymbol;
    }
  } else {
    while (playerSymbol != 'h' && playerSymbol != 'd' && playerSymbol != 'e' &&
           playerSymbol != 'o' && playerSymbol != 'q') {
      cout << "Invalid character. Please try again." << endl;
      cin >> playerSymbol;
    }
  }
  playerSymbol = Symbol;
  displayGrid = defaultMap;
  level = 1;
  stairVisible = false;
  barrierFloor = randomNum(5) + 1;
  cout << RESET;
  init();
}
