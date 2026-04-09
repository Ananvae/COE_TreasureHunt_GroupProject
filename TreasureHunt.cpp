#include "TreasureHunt.h"
#include <iostream>
#include <fstream>
using namespace std;

// If score drops below this the player loses
const int LOSE_THRESHOLD = 0;

// Any map tile with one of these letters is a landmark
const string LANDMARK_CHARS = "TPHUGF";

// Constructor/destructor:

TreasureHunt::TreasureHunt() {
    playerRow = 0;
    playerCol = 0;
    totalLandmarks = 0;
    completedLandmarks = 0;
    gameOver = false;

    // Allocating score on the heap which means score persists across function calls without being passed around
    scorePtr = new int(0);
}

TreasureHunt::~TreasureHunt() {
    // Every new needs a matching delete
    // Clean up the heap score
    delete scorePtr;
    scorePtr = nullptr;
}

// Reads map.txt line by line into the grid vector
// Also finds the @ starting position for the player
bool TreasureHunt::loadMap(const string& filename) {
    ifstream myFile;
    myFile.open(filename);

    if (myFile.is_open()) {
        string line;
        int atSignCount = 0;

        while (myFile >> line) {
            // Scan each character to find @ and count landmarks
            for (int col = 0; col < line.size(); col++) {
                char ch = line[col];
                if (ch == '@') {
                    playerRow = grid.size();
                    playerCol = col;
                    atSignCount++;
                }
            }
            grid.push_back(line);
        }

        myFile.close();

        if (atSignCount != 1) {
            cout << "Map must have exactly one @ start position." << endl;
            return false;
        }

        // Count all the landmark tiles so we know the win condition
        for (int r = 0; r < grid.size(); r++) {
            for (int c = 0; c < grid[r].size(); c++) {
                if (isLandmark(grid[r][c]))
                    totalLandmarks++;
            }
        }

        return true;

    } else {
        cout << "Failed to open " << filename << endl;
        return false;
    }
}

// Reads clues.txt 
// Each line format as instructed: Symbol|Question|Answer|MaxAttempts|Points
bool TreasureHunt::loadClues(const string& filename) {
    ifstream myFile;
    myFile.open(filename);

    if (myFile.is_open()) {
        string line;

        // Because questions like "In what year was the UT Tower completed?" have spaces we use getline instead of cin
        while (getline(myFile, line)) {
            if (line.empty()) continue;

            // Search each field by finding the | separators one at a time
            // Using find() and substr() which are standard string operations
            int pos1 = line.find('|');
            int pos2 = line.find('|', pos1 + 1);
            int pos3 = line.find('|', pos2 + 1);
            int pos4 = line.find('|', pos3 + 1);

            // If any separator is missing, skip this line
            if (pos1 == string::npos || pos2 == string::npos ||
                pos3 == string::npos || pos4 == string::npos)
                continue;

            // Pull each field out using substr
            string symStr   = line.substr(0, pos1);
            string question = line.substr(pos1 + 1, pos2 - pos1 - 1);
            string answer   = line.substr(pos2 + 1, pos3 - pos2 - 1);
            string attStr   = line.substr(pos3 + 1, pos4 - pos3 - 1);
            string ptsStr   = line.substr(pos4 + 1);

            char sym     = symStr[0];
            int attempts = stoi(attStr);
            int pts      = stoi(ptsStr);

            // Build a Clue object and add it to our vector
            clues.push_back(Clue(sym, question, answer, attempts, pts));
        }

        myFile.close();
        return true;

    } else {
        cout << "Failed to open " << filename << endl;
        return false;
    }
}

// Drawing:

// Redraws the entire map to the console each turn
void TreasureHunt::drawMap() {
    // Clear screen: works on most terminals
    cout << "\033[2J\033[H";

    cout << "=== UT Campus Treasure Hunt ===" << endl;
    cout << "Score: " << *scorePtr
         << "  |  Landmarks: " << completedLandmarks << "/" << totalLandmarks << endl;
    cout << endl;

    for (int r = 0; r < grid.size(); r++) {
        for (int c = 0; c < grid[r].size(); c++) {
            // draw @ on top of whatever tile the player is standing on
            if (r == playerRow && c == playerCol) {
                cout << "\033[34m" << '@' << "\033[0m";   // blue curent location (@)
            }
            else if (isLandmark(grid[r][c])) {
                Clue* clue = findClue(grid[r][c]);
                if (clue != nullptr && clue->completed)
                    cout << "\033[32m" << grid[r][c] << "\033[0m";  // green visited landmarks
                else
                    cout << "\033[31m" << grid[r][c] << "\033[0m";  // red unvisited landmarks
            }
            else {
                cout << grid[r][c];
            }
        }
        cout << endl;
    }

    cout << endl;
    cout << "Move: W/A/S/D  |  Q to quit" << endl;
}

// Movement:

// Handles one W/A/S/D keypress
// Checks walls and bounds before moving
void TreasureHunt::movePlayer(char direction) {
    int newRow = playerRow;
    int newCol = playerCol;

    if      (direction == 'w' || direction == 'W') newRow--;
    else if (direction == 's' || direction == 'S') newRow++;
    else if (direction == 'a' || direction == 'A') newCol--;
    else if (direction == 'd' || direction == 'D') newCol++;
    else return;   // Anything else we just ignore

    // Make sure we didn't walk off the edge of the map
    if (newRow < 0 || newRow >= grid.size())         return;
    if (newCol < 0 || newCol >= grid[newRow].size()) return;

    char tile = grid[newRow][newCol];

    // # is a wall so we can't go there
    if (tile == '#') return;

    // Move the player
    playerRow = newRow;
    playerCol = newCol;

    // If they stepped onto a landmark tile, kick off the clue challenge
    if (isLandmark(tile)) {
        triggerClue(tile);
    }
}

// Clue challenge:

// Runs the Q&A when the player lands on a landmark
void TreasureHunt::triggerClue(char landmarkSym) {
    Clue* clue = findClue(landmarkSym);

    if (clue == nullptr) {
        cout << "No clue found for this landmark." << endl;
        return;
    }

    // If player already completed this one skip it
    if (clue->completed) {
        cout << endl << "[Already completed this landmark! Keep moving.]" << endl;
        return;
    }

    cout << "** Landmark Unlocked! **" << endl;
    cout << "Question: " << clue->question << endl;
    cout << "You have " << clue->maxAttempts << " attempt(s). "
         << "Worth " << clue->points << " points." << endl;
    cout << endl;

    int attemptsLeft = clue->maxAttempts;
    bool gotItRight = false;

    while (attemptsLeft > 0) {
        cout << "Your answer: ";
        string guess;
        getline(cin, guess);

        if (clue->checkAnswer(guess)) {
            gotItRight = true;
            break;
        } else {
            attemptsLeft--;
            if (attemptsLeft > 0)
                cout << "Not quite! " << attemptsLeft << " attempt(s) left." << endl;
        }
    }

    if (gotItRight) {
        cout << "Correct! +" << clue->points << " points!" << endl;
        applyScoreDelta(*scorePtr, clue->points);   // Pass by reference requirement
        clue->completed = true;
        completedLandmarks++;

    } else {
        // Missed all attempts 
        // Lose half the clue's point value as a penalty
        int penalty = clue->points / 2;
        cout << "Out of attempts. The answer was: " << clue->answer << endl;
        cout << "You lose " << penalty << " points." << endl;
        applyScoreDelta(*scorePtr, -penalty);
        clue->completed = true;
        completedLandmarks++;

        // Check if score dropped below zero
        if (*scorePtr < LOSE_THRESHOLD) {
            cout << endl << "Score dropped below 0 - game over!" << endl;
            gameOver = true;
        }
    }
    cout << "Press Enter to continue...";
    cin.ignore();
}

// Main game loop:

void TreasureHunt::startGame() {
    if (grid.empty() || clues.empty()) {
        cout << "Game data not loaded. Make sure map.txt and clues.txt exist." << endl;
        return;
    }

    while (!gameOver) {
        drawMap();

        // Win condition- All landmarks visited
        if (completedLandmarks >= totalLandmarks) {
            cout << endl << "You found all the landmarks!" << endl;
            break;
        }

        cout << "Enter move: ";
        string input;
        getline(cin, input);

        if (input.empty()) continue;

        char cmd = input[0];

        if (cmd == 'q' || cmd == 'Q') {
            cout << "Quitting..." << endl;
            gameOver = true;
            break;
        }

        movePlayer(cmd);
    }
    displayFinalResult();
}

// End screen:

void TreasureHunt::displayFinalResult() const {
    cout << "=== GAME OVER ===" << endl;
    cout << "Final Score: " << *scorePtr << endl;

    // Calculate completion percentage
    double pct = 0.0;
    if (totalLandmarks > 0)
        pct = 100.0 * completedLandmarks / totalLandmarks;

    cout << "Landmarks Completed: " << completedLandmarks
         << "/" << totalLandmarks
         << " (" << (int)pct << "%)" << endl;

    if (completedLandmarks >= totalLandmarks && *scorePtr >= LOSE_THRESHOLD)
        cout << "You WIN! Hook 'em!" << endl;
    else
        cout << "Better luck next time. The 40 Acres will still be here." << endl;
}

// Private helpers:

// Walks the clues vector and returns a pointer to the one matching sym
// Returns nullptr if nothing matches
Clue* TreasureHunt::findClue(char sym) {
    for (int i = 0; i < clues.size(); i++) {
        if (clues[i].symbol == sym)
            return &clues[i];
    }
    return nullptr;
}

// True if the tile letter is one of our defined landmark characters
bool TreasureHunt::isLandmark(char tile) const {
    for (int i = 0; i < LANDMARK_CHARS.size(); i++) {
        if (LANDMARK_CHARS[i] == tile)
            return true;
    }
    return false;
}

// Adds delta to whatever score variable is passed in
// Using a reference here so we directly modify the caller's variable
// This is the pass-by-reference requirement from the assignment
void TreasureHunt::applyScoreDelta(int& score, int delta) {
    score += delta;
}

// Wrapper: passes the heap-allocated score into applyScoreDelta by reference
void TreasureHunt::updateScore(int delta) {
    applyScoreDelta(*scorePtr, delta);
}

