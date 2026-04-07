#include <iostream>
#include "TreasureHunt.h"
using namespace std;

int main() {
    TreasureHunt game;
    if (!game.loadMap("map.txt")) {
        cout << "Failed to load map.txt" << endl;
        return 1;
    }
    if (!game.loadClues("clues.txt")) {
        cout << "Failed to load clues.txt" << endl;
        return 1;
    }
    game.startGame();

    return 0;
}
