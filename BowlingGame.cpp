#include "BowlingGame.h"

BowlingGame::BowlingGame() : currentRoll(0), currentFrame(0) {
    // Initialize arrays with zeros using range-based for loop
    for (int& roll : rolls) roll = 0;
    for (int& score : scores) score = 0;
}

void BowlingGame::roll(int pins) {
    rolls[currentRoll++] = pins;
    if (currentFrame < 9) { // Frames 1-9
        if (pins == 10 || currentRoll % 2 == 0) { // Strike or second roll of frame
            currentFrame++;
        }
    } else { // 10th frame special case
        if (currentRoll == 1 && pins == 10) { // Strike on first roll of 10th frame
            // Allow two more rolls
        } else if (currentRoll == 2) {
            if (rolls[currentRoll - 2] == 10 || rolls[currentRoll - 2] + rolls[currentRoll - 1] == 10) {
                // Spare or second strike allows one more roll
            } else {
                currentFrame++; // No bonus roll if less than a spare
            }
        } else if (currentRoll == 3) {
            currentFrame++; // End after third roll in the 10th frame
        }
    }
    calculateScore();  // Recalculate scores after each roll
    printCurrentScore();      // Print the results on the screen
}

int BowlingGame::getScore() const {
    return scores[9]; // Return the score after the 10th frame
}

int BowlingGame::getCurrentFrame() const {
    return currentFrame + 1;
}

bool BowlingGame::isGameOver() const {
    return currentFrame >= 10;
}

void BowlingGame::printCurrentScore() const {
    constexpr int columnWidth = 5; // Set column width to 5 to accommodate up to 3 values with surrounding space

    // Line Frame
    std::cout << "Frame:  ";
    for (int i = 1; i <= 10; i++) {
        std::cout << "|" << std::setw(columnWidth) << i;
    }
    std::cout << "|" << std::endl;

    // Line Throw:
    std::cout << "Throw:  ";
    int rollIndex = 0;
    for (int frame = 0; frame < 10; frame++) {
        std::cout << "|";
        if (rolls[rollIndex] == 10) { // Strike
            std::cout << std::setw(columnWidth - 1) << "X";
            rollIndex++;
        } else {
            if (rollIndex < currentRoll) {
                std::cout << std::setw(2) << rolls[rollIndex];
            } else {
                std::cout << std::setw(columnWidth - 1) << " ";
            }
            rollIndex++;
            if (rollIndex < currentRoll) {
                if (rolls[rollIndex - 1] + rolls[rollIndex] == 10) {
                    std::cout << std::setw(3) << "/";
                } else {
                    std::cout << std::setw(3) << rolls[rollIndex];
                }
            } else {
                std::cout << std::setw(columnWidth - 2) << " ";
            }
            rollIndex++;
        }
    }
    std::cout << "|" << std::endl;

    // Line Score
    std::cout << "Score:  ";
    for (int i = 0; i < 10; i++) {
        std::cout << "|" << std::setw(columnWidth - 1) << scores[i];
    }
    std::cout << "|" << std::endl << std::endl;
}

bool BowlingGame::isTenthFrameExtraRoll() const {
    return currentFrame == 9 && currentRoll >= 2 && (rolls[18] == 10 || rolls[18] + rolls[19] == 10);
}

bool BowlingGame::isStrike(int rollIndex) const {
    return rolls[rollIndex] == 10;
}

bool BowlingGame::isSpare(int rollIndex) const {
    return rolls[rollIndex] + rolls[rollIndex + 1] == 10;
}

int BowlingGame::strikeBonus(int rollIndex) const {
    return rolls[rollIndex + 1] + rolls[rollIndex + 2];
}

int BowlingGame::spareBonus(int rollIndex) const {
    return rolls[rollIndex + 2];
}

int BowlingGame::frameScore(int rollIndex) const {
    return rolls[rollIndex] + rolls[rollIndex + 1];
}

void BowlingGame::calculateScore() {
    int frameIndex = 0;
    for (int frame = 0; frame < 10; frame++) {
        if (isStrike(frameIndex)) { // Strike
            scores[frame] = 10 + strikeBonus(frameIndex);
            frameIndex++;
        } else if (isSpare(frameIndex)) { // Spare
            scores[frame] = 10 + spareBonus(frameIndex);
            frameIndex += 2;
        } else { // Normal frame
            scores[frame] = frameScore(frameIndex);
            frameIndex += 2;
        }

        // Add to previous frames
        if (frame > 0) scores[frame] += scores[frame - 1];
    }
}