#include <iostream>
#include <vector>
#include <string>
#include "Clue.h"
using namespace std;

// Main game class: handles the map, the player, clues, and score
class TreasureHunt {
public:
    // Sets up default starting values
    TreasureHunt();
    // Cleans up our heap score pointer
    ~TreasureHunt();
    // Reads the map grid from a text file
    bool loadMap(const string& filename);
    // Reads all the clues from a pipe-delimited text file
    bool loadClues(const string& filename);
    // Redraws the map to the console each turn
    void drawMap() const;
    // Moves the player based on W/A/S/D input
    void movePlayer(char direction);
    // Runs the Q&A challenge when the player steps on a landmark
    void triggerClue(char landmarkSym);
    // The main game loop: runs until win or loss
    void startGame();
    // Prints the final score and result at the end
    void displayFinalResult() const;

private:
    vector<string> grid;   // Each string is one row of the map
    int playerRow;
    int playerCol;
    vector<Clue> clues;    // All the landmark clues loaded from file
    int* scorePtr;         // Score lives on the heap (meets pointer requirement)
    int totalLandmarks;
    int completedLandmarks;
    bool gameOver;
    // Looks through the clues vector and returns a pointer to the matching one
    Clue* findClue(char sym);
    // Returns true if the tile character is one of our landmark letters
    bool isLandmark(char tile) const;
    // Adds or subtracts points — uses a reference parameter (meets requirement)
    void applyScoreDelta(int& score, int delta);
    // Thin wrapper that calls applyScoreDelta with our heap score
    void updateScore(int delta);
    // Just prints a divider line to the console
    void printDivider() const;
};
