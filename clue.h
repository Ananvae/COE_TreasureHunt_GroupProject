#include <iostream>
#include <string>
using namespace std;

// this class holds all the info for one landmark clue
// each landmark on the map gets its own Clue object
class Clue {
public:
    char symbol;        // the letter on the map (T, P, H, etc.)
    string question;
    string answer;
    int maxAttempts;
    int points;
    bool completed;     // tracks if the player already visited this landmark

    // constructor- fills everything in when we create a Clue
    Clue(char sym, string q, string ans, int attempts, int pts);

    // will return true if the player's guess matches the correct answer
    // case-insensitive so "TOWER" and "tower" both count
    bool checkAnswer(const string& guess) const;

    //converts any string to all lowercase for comparison
    static string toLower(const string& s);
};
