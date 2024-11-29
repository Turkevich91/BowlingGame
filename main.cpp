#include "BowlingGame.h"
#include <string>

int main() {
    BowlingGame game;
    std::string filename;

    std::cout << "Enter the filename to load the game (e.g., bowler1.txt): ";
    std::cin >> filename;
    std::cout << std::endl;

    // Load the game from the file
    game.loadGameFromFile(filename);

    return 0;
}
