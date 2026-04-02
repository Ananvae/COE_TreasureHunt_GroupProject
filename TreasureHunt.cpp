#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include "TreasureHunt.h"



using namespace std;
//loading the map from the file and printing it to the console
class TreasureHunt {
public:
    bool loadMap(const std::string& filename) {
        std::ifstream mapFile(filename);
        if (mapFile.is_open()) {
            std::string line;
            while (getline(mapFile, line)) {
                std::cout << line << std::endl;
            }
            return true;
        } else {
            std::cout << "Unable to open the map file BRAH" << std::endl;
            return false;
        }
    }
};
