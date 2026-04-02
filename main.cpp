#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <fstream>
#include "TreasureHunt.h"
#include "clue.h"

using namespace std;

   void slowPrint9(string str){  // Function to print out things slowly, like a type writer!:D
        for (char c : str) {
            cout << c;
            this_thread::sleep_for(chrono::milliseconds(50));
        }
        cout << endl;
    }
int main(){
    // Introduction prints to the user, explaining the game and what to expect
    slowPrint9("Welcome! To the UT Treasure Hunt Game! ヽ(・∀・)ﾉ ࣪");
    slowPrint9("You will be given a map! As a UT student, you will have to find your way through the map answering questions along the way...☆ ～('▽ ^ 人)");
    slowPrint9("I'm generating the map now! Please wait...");
    this_thread::sleep_for(chrono::seconds(3));
    slowPrint9("Here is your map! Good luck and have fun~");  
    // Printing map from the TreasureHunt class, which is loaded from the map.txt file
    TreasureHunt treasureHunt;
    treasureHunt.loadMap("map.txt"); // Load the map from the file and print it to the console
}