#include <fstream>
#include <iostream>
#include <string>

#include "game.h"

using namespace std;

int main(int argc, char *argv[]) {
  const std::string BOLD = "\033[1m";
  const std::string RESET = "\033[0m";
  cout << BOLD;
  cout << "Welcome to CC3K!" << endl;
  char playerSymbol;
  bool bonus = false;
  cout << "Bonus Content? (y/n):" << endl;
  cin >> playerSymbol;
  while (playerSymbol != 'y' && playerSymbol != 'n') {
    cout << "Invalid input. Please enter (y) or (n):" << endl;
    cin >> playerSymbol;
  }
  if (playerSymbol == 'y') {
    cout << "You have chosen to play with a bonus content!" << endl;
    cout << "Bonus Content: " << endl;
    cout << "Vampire has lifesteal" << endl;
    cout << "Good luck!" << endl;
    bonus = true;
  } else {
    cout << "You have chosen to play without a bonus content!" << endl;
    cout << "Good luck!" << endl;
  }
  cout << "Please choose your character:" << endl;
  cout << "Human (h)" << endl;
  cout << "Dwarf (d)" << endl;
  cout << "Elf (e)" << endl;
  cout << "Orc (o)" << endl;
  if (bonus) {
    cout << "God (g) (do not need to specify directions when attacking)" << endl;
    cout << "Magic Archer (m)" << endl;
    cout << "Valkyrie (v) (do not need to specify directions when attacking)" << endl;
  }
  cout << "Quit (q)" << endl;

  cin >> playerSymbol;
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
  cout << RESET;
  if (playerSymbol == 'q') {
    return 0;
  }
  Game game(playerSymbol, bonus);
  if (argc == 2) {
    string filename = argv[1];
    game.changeMap(filename);
  } else {
    game.changeMap("defaultMap.txt");
  }
  game.play();
}