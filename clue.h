#include <iostream>
#include <string>
using namespace std;

// This class holds all the info for one landmark clue
// Each landmark on the map gets its own Clue object
class Clue {
public:
    char symbol;        // The letter on the map (T, P, H, etc.)
    string question;
    string answer;
    int maxAttempts;
    int points;
    bool completed;     // Tracks if the player already visited this landmark

    // Constructor: fills everything in when we create a Clue
    Clue(char sym, string q, string ans, int attempts, int pts);

    // Will return true if the player's guess matches the correct answer
    // Case-insensitive so "TOWER" and "tower" both count
    bool checkAnswer(const string& guess) const;

    //Converts any string to all lowercase for comparison
    static string toLower(const string& s);
};
