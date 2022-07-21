#include "game.h"
#include <iostream>

using namespace std;

<<<<<<< HEAD
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
=======
int main(int argc, char *argv[]) {
    char r = 'h';
    if (argc != 1 && (*argv[1] == 'e' || *argv[1] == 'h' || *argv[1] == 'd' || *argv[1] == 'o')) {
        r = *argv[1];
    }
    Game game(r);
>>>>>>> 56f211e6fd91411d70141c4ffe57a186bcde080f
    game.play();
}