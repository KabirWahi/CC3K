#include "game.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
    char r = 'h';
    if (argc != 1 && (*argv[1] == 'e' || *argv[1] == 'h' || *argv[1] == 'd' || *argv[1] == 'o')) {
        r = *argv[1];
    }
    Game game(r);
    game.play();
    return 0;
}