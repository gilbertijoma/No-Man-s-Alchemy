

#include "Game.h"

#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
using namespace std;

int main () {
    srand(time(NULL));
    Game newGame;
    newGame.StartGame();
    return 0;
}
