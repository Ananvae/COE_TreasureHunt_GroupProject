#include <iostream>
#include <vector>
#include <string>
#include "Clue.h"
using namespace std;

// main game class- handles the map, the player, clues, and score
class TreasureHunt {
public:
    // sets up default starting values
    TreasureHunt();
    // cleans up our heap score pointer
    ~TreasureHunt();
    // reads the map grid from a text file
    bool loadMap(const string& filename);
    // reads all the clues from a pipe-delimited text file
    bool loadClues(const string& filename);
    // redraws the map to the console each turn
    void drawMap() const;
    // moves the player based on W/A/S/D input
    void movePlayer(char direction);
    // runs the Q&A challenge when the player steps on a landmark
    void triggerClue(char landmarkSym);
    // the main game loop- runs until win or loss
    void startGame();
    // prints the final score and result at the end
    void displayFinalResult() const;

private:
    vector<string> grid;   // each string is one row of the map
    int playerRow;
    int playerCol;
    vector<Clue> clues;    // all the landmark clues loaded from file
    int* scorePtr;         // score lives on the heap (meets pointer requirement)
    int totalLandmarks;
    int completedLandmarks;
    bool gameOver;
    // looks through the clues vector and returns a pointer to the matching one
    Clue* findClue(char sym);
    // returns true if the tile character is one of our landmark letters
    bool isLandmark(char tile) const;
    // adds or subtracts points — uses a reference parameter (meets requirement)
    void applyScoreDelta(int& score, int delta);
    // thin wrapper that calls applyScoreDelta with our heap score
    void updateScore(int delta);
    // just prints a divider line to the console
    void printDivider() const;
};
