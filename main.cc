#include "game.h"
#include <iostream>

using namespace std;

int main() {
    cout << "Welcome to CC3K!" << endl;
    cout << "Please choose your character:" << endl;
    cout << "Human (h)" << endl;
    cout << "Dwarf (d)" << endl;
    cout << "Elf (e)" << endl;
    cout << "Orc (o)" << endl;
    char playerSymbol;
    cin >> playerSymbol;
    while (playerSymbol != 'h' && playerSymbol != 'd' && playerSymbol != 'e' && playerSymbol != 'o') {
        cout << "Invalid character. Please try again." << endl;
        cin >> playerSymbol;
    }
    Game game(playerSymbol);
    game.play();
}