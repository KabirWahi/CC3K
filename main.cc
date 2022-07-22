#include "game.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main(int argc, char *argv[]) {
    const std::string BOLD = "\033[1m";
    const std::string RESET = "\033[0m";
    cout << BOLD;
    cout << "Welcome to CC3K!" << endl;
    cout << "Please choose your character:" << endl;
    cout << "Human (h)" << endl;
    cout << "Dwarf (d)" << endl;
    cout << "Elf (e)" << endl;
    cout << "Orc (o)" << endl;
    cout << "Quit (q)" << endl;
    char playerSymbol;
    cin >> playerSymbol;
    while (playerSymbol != 'h' && playerSymbol != 'd' && playerSymbol != 'e' && playerSymbol != 'o' && playerSymbol != 'q') {
        cout << "Invalid character. Please try again." << endl;
        cin >> playerSymbol;
    }
    cout << RESET;
    if (playerSymbol == 'q') {
        return 0;
    }
    Game game(playerSymbol);
    if (argc == 2) {
        string filename = argv[1];
        game.changeMap(filename);
    } else {
        game.changeMap("defaultMap.txt");
    }
    game.play();
}