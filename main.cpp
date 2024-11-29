#include "BowlingGame.h"
#include <string>

int main() {
    BowlingGame game;
    std::string filename;

    std::cout << "Enter the filename to load the game (e.g., bowler1.txt): ";
    std::cin >> filename;

    // Load the game from the file
    game.loadGameFromFile(filename);

    // Print the final score after all frames have been played
    std::cout << "Final score: " << game.getScore() << std::endl;

    return 0;
}
