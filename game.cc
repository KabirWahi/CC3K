#include "game.h"

#include <time.h>

#include <algorithm>
#include <chrono>
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

Game::Game(char playerSymbol)
    : playerSymbol(playerSymbol),
      level(1),
      stairVisible(false),
      barrierFloor{randomNum(5) + 1} {
  string map[25] = {
      "|-----------------------------------------------------------------------------|",
      "|                                                                             |",
      "| |--------------------------|        |-----------------------|               |",
      "| |..........................|        |.......................|               |",
      "| |..........................+########+.......................|-------|       |",
      "| |..........................|   #    |...............................|--|    |",
      "| |..........................|   #    |..................................|--| |",
      "| |----------+---------------|   #    |----+----------------|...............| |",
      "|            #                 #############                |...............| |",
      "|            #                 #     |-----+------|         |...............| |",
      "|            #                 #     |............|         |...............| |",
      "|            ###################     |............|   ######+...............| |",
      "|            #                 #     |............|   #     |...............| |",
      "|            #                 #     |-----+------|   #     |--------+------| |",
      "|  |---------+-----------|     #           #          #              #        |",
      "|  |.....................|     #           #          #         |----+------| |",
      "|  |.....................|     ########################         |...........| |",
      "|  |.....................|     #           #                    |...........| |",
      "|  |.....................|     #    |------+--------------------|...........| |",
      "|  |.....................|     #    |.......................................| |",
      "|  |.....................+##########+.......................................| |",
      "|  |.....................|          |.......................................| |",
      "|  |---------------------|          |---------------------------------------| |",
      "|                                                                             |",
      "|-----------------------------------------------------------------------------|"};

  for (int i = 0; i < 25; i++) {
    defaultMap.push_back(vector<char>());
    for (int j = 0; j < 79; j++) {
      defaultMap[i].push_back(map[i][j]);
    }
  }
  displayGrid = defaultMap;
}

void Game::init() {
  generatePlayer(playerSymbol);
  int row = 0;
  int col = 0;
  int chamber = randomNum(5) + 1;
  while (chamber == player->getPosition().whichChamber()) {
    chamber = randomNum(5) + 1;
  }
  while (displayGrid[row][col] != '.' ||
         (Posn{row, col}).whichChamber() != chamber) {
    row = randomNum(25);
    col = randomNum(79);
  }
  stairPosition = Posn{row, col};
  displayGrid[row][col] = '\\';
  generateItems();
  generateEnemies();
  displayGrid[row][col] = '.';
}

Posn Game::randomPosn(int chamber) {
  int row = randomNum(25);
  int col = randomNum(79);
  while (displayGrid[row][col] != '.' ||
         (Posn{row, col}).whichChamber() != chamber) {
    row = randomNum(25);
    col = randomNum(79);
  }
  return Posn{row, col};
}

Posn randomNeighbour(Posn posn) {
  int row = posn.row;
  int col = posn.col;
  int neighbour = randomNum(8);
  row += r[neighbour];
  col += c[neighbour];
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
        if (tmp == '.' || tmp == '+' || tmp == '#') {
          moved = true;
          player->setPosition(Posn{player->getPosition().row + r[i],
                                   player->getPosition().col + c[i]});
          msg = "You moved " + directions[i] + ". ";
          break;
        } else if (tmp == 'G') {
          moved = true;
          player->setPosition(Posn{player->getPosition().row + r[i],
                                   player->getPosition().col + c[i]});
          for (auto it : items) {
            if (it->getPosition() == player->getPosition()) {
              int gold = it->getValue();
              player->setGold(player->getGold() + gold);
              msg = "You moved " + directions[i] + " and picked up " +
                    to_string(gold) + " gold. ";
              displayGrid[it->getPosition().row][it->getPosition().col] = '.';
              items.erase(remove(items.begin(), items.end(), it), items.end());
              break;
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
            if (potionpos == it->getPosition()) {
              if (it->getId() == 0 || it->getId() == 3) {
                player->addHealth(it->getValue());
              }
              if (it->getId() == 1) {
                player = new AtkBuff(player, "BA");
              }
              if (it->getId() == 2) {
                player = new DefBuff(player, "BD");
              }
              if (it->getId() == 4) {
                player = new AtkBuff(player, "WA");
              }
              if (it->getId() == 5) {
                player = new DefBuff(player, "WD");
              }
              msg = "PC picked up a potion. ";
              moved = true;
              break;
            }
          }
        }
      }
    }
    if (input == "q") {
      break;
    }
    if (!moved) {
      cout << "Invalid move. " << endl;
      continue;
    }
    msg = msg + update();
    print();
    cout << msg << endl;
    if (player->getHP() <= 0) {
      cout << "You died :( " << endl;
      break;
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
      player->setGold(player->getGold() + en->getGold());
      msg = msg + "You slained " + (en->getSymbol()) + " and got " +
            to_string(en->getGold()) + " gold. ";
      if (en->compass) {
        items.emplace_back(new Compass(en->getPosition()));
      }
      enemies.erase(remove(enemies.begin(), enemies.end(), en), enemies.end());
      continue;
    }
    for (int i = 0; i < 8; i++) {
      Posn enemyattack =
          Posn{en->getPosition().row + r[i], en->getPosition().col + c[i]};
      if (enemyattack == player->getPosition()) {
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
    if (attacked) {
      continue;
    }
    int di = randomNum(8);
    while (!moved) {
      if (displayGrid[en->getPosition().row + r[di]][en->getPosition().col + c[di]] == '.') {
        en->setPosition(Posn{en->getPosition().row + r[di], en->getPosition().col + c[di]});
        moved = true;
      } else {
        di = randomNum(8);
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
  player = new Human(posn);
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
  int numEnemies = 3;
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
  int compassHolder = 0;
  enemies[compassHolder]->compass = true;
  cout << "Enemy " << enemies[compassHolder]->getRace() << enemies[compassHolder]->getPosition().row << " "
       << enemies[compassHolder]->getPosition().col << " has a compass. " << endl;
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
  delete player;
  init();
  player->setHP(HP);
  player->setGold(Gold);
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
       << endl;
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
    int type = randomNum(6);  // 0 - RH, 1 - BA, 2 - BD, 3 - PH, 4 - WA, 5 - WD
    items.emplace_back(new Potion(0 + type, posn));
    displayGrid[posn.row][posn.col] = 'P';
  }
  int numGolds = 10;
  for (int i = 0; i < numGolds; i++) {
    int chamber = randomNum(5) + 1;
    Posn posn = randomPosn(chamber);
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
    BarrierSuit *bar = new BarrierSuit(posn);
    items.emplace_back(bar);
    displayGrid[posn.row][posn.col] = 'B';
    Posn dragonPosn = randomNeighbour(posn);
    enemies.push_back(new Dragon(dragonPosn, bar));
    displayGrid[dragonPosn.row][dragonPosn.col] = 'D';
  }
}
