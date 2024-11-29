#include "BowlingGame.h"

int main() {
    BowlingGame game;
    int pins;

    std::cout << "Enter the result of each throw in order:" << std::endl;
    while (!game.isGameOver()) {
        std::cout << "Throw: ";
        std::cin >> pins;
        std::cout << std::endl;

        if (pins < 0 || pins > 10) {
            std::cout << "Invalid input. Please enter a value between 0 and 10." << std::endl;
            continue;
        }

        game.roll(pins);
    }

    std::cout << "Final score: " << game.getScore() << std::endl;
    return 0;
}
