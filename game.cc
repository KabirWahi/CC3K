#include "game.h"
#include <string>
#include <iostream>
using namespace std; 

Game::Game(char playerSymbol) : playerSymbol(playerSymbol), level(1), stairVisible(false), barrierFloor{rand() % 5 + 1} {
    string map[25] = {"|-----------------------------------------------------------------------------|",
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
        for (int j = 0; j < 80; j++) {
            defaultMap[i].push_back(map[i][j]);
        }
    }
    displayGrid = defaultMap;
    init();
}


void Game::init() {
    generatePlayer(playerSymbol);
    int row = 0;
    int col = 0;
    int chamber = rand() % 5 + 1;
    while (chamber == getChamber(player->getPosition())) {
        chamber = rand() % 5 + 1;
    }
    while (displayGrid[row][col] != '.' || getChamber(Posn{row, col}) != chamber) {
        row = rand() % 25;
        col = rand() % 80;
    }
    stairPosition = Posn{row, col};
    displayGrid[row][col] = '\\';
    if (getLevel() == barrierFloor) {
        int chamber = rand() % 5 + 1;
        Posn posn = randomPosn(chamber);
        displayGrid[posn.row][posn.col] = 'B';
        // Add dragon code here
    }
    generateItems();
    generateEnemies();
    displayGrid[row][col] = '.';
}

Posn Game::randomPosn(int chamber) {
    int row = rand() % 25;
    int col = rand() % 80;
    while (displayGrid[row][col] != '.' || getChamber(Posn{row, col}) != chamber) {
        row = rand() % 25;
        col = rand() % 80;
    }
    return Posn{row, col};
}


void Game::generatePlayer(char symbol) {
    int chamber = rand() % 5 + 1;
    Posn posn = randomPosn(chamber);
    if (playerSymbol == 'h') {
        player = new Human(posn);
    } else if (playerSymbol == 'd') {
        player = new Dwarf(posn);
    } else if (playerSymbol == 'e') {
        player = new Elf(posn);
    } else {
        player = new Orc(posn);
    }
    displayGrid[posn.row][posn.col] = '@';
}

void Game::generateEnemies() {
    for (int i = 0; i < 20 - enemies.size(); i++) {
        int chamber = rand() % 5 + 1;
        Posn posn = randomPosn(chamber);
        int type = rand() % 18; // 0 - 3 Werewolf, 4 - 6 Vampire, 7 - 11 Goblin, 12 - 13 Troll,
        if (type < 4) { // 14 - 15 Pheonix, 16 - 17 Merchant
            enemies.push_back(new Werewolf(posn));
            displayGrid[posn.row][posn.col] = 'W';
        } else if (type < 6) {
            enemies.push_back(new Vampire(posn));
            displayGrid[posn.row][posn.col] = 'V';
        } else if (type < 11) {
            enemies.push_back(new Goblin(posn));
            displayGrid[posn.row][posn.col] = 'N';
        } else if (type < 13) {
            enemies.push_back(new Troll(posn));
            displayGrid[posn.row][posn.col] = 'T';
        } else if (type < 14) {
            enemies.push_back(new Phoenix(posn));
            displayGrid[posn.row][posn.col] = 'X'; 
        } else {
            enemies.push_back(new Merchant(posn));
            displayGrid[posn.row][posn.col] = 'M';
        }
    }
    int compassHolder = rand() % 20;
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
    delete player;
    init();
    player->setHP(HP);
    player->setGold(Gold);
    if (hasBarrier) {
        player->toggleBarrier();
    }
}

int Game::getLevel() {
    return level;
}

Player* Game::getPlayer() {
    return player;
}

Posn Game::getStairs() {
    return stairPosition;
}

void Game::print() {
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 80; j++) {
            cout << displayGrid[i][j];
        }
        cout << endl;
    }
}

