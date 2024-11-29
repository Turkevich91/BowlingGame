// BowlingGame.cpp
#include "BowlingGame.h"
#include <fstream>

BowlingGame::BowlingGame() : currentRoll(0), currentFrame(0) {
    // Initialize arrays with zeros
    for (int& roll : rolls) roll = 0;
    for (int& score : scores) score = 0;
}

void BowlingGame::roll(const int pins) {
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
    if (currentRoll % 2 == 0 || pins == 10 || currentFrame == 10) {
        printScore();  // Print the results after each frame
    }
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

void BowlingGame::printScore() const {
    constexpr int columnWidth = 6; // Set column width to 6 for better formatting

    // Only print frames that have been played
    std::cout << "Frame:  ";
    for (int i = 0; i < currentFrame; i++) {
        std::string frameNum = std::to_string(i + 1);
        int padding = (columnWidth - frameNum.length()) / 2;
        std::cout << "|" << std::string(padding, ' ') << frameNum << std::string(columnWidth - padding - frameNum.length(), ' ');
    }
    std::cout << "|" << std::endl;

    // Line Throw:
    std::cout << "Throw:  ";
    int rollIndex = 0;
    for (int frame = 0; frame < currentFrame; frame++) {
        std::cout << "|";
        std::string throwStr;
        if (isStrike(rollIndex)) { // Strike
            throwStr = "10";
        } else {
            throwStr = std::to_string(rolls[rollIndex]);
            rollIndex++;
            if (rollIndex < currentRoll) {
                throwStr += " " + std::to_string(rolls[rollIndex]);
            }
        }
        int padding = (columnWidth - throwStr.length()) / 2;
        std::cout << std::string(padding, ' ') << throwStr << std::string(columnWidth - padding - throwStr.length(), ' ');
        rollIndex++;
    }
    std::cout << "|" << std::endl;

    // Line Score
    std::cout << "Score:  ";
    for (int i = 0; i < currentFrame; i++) {
        std::string scoreStr = (isStrike(i) ? "X" : (isSpare(i) ? "/" : std::to_string(scores[i])));
        int padding = (columnWidth - scoreStr.length()) / 2;
        std::cout << "|" << std::string(padding, ' ') << scoreStr << std::string(columnWidth - padding - scoreStr.length(), ' ');
    }
    std::cout << "|" << std::endl << std::endl;
}


bool BowlingGame::isTenthFrameExtraRoll() const {
    // Corrected logic to ensure that the extra roll in the 10th frame is accurately handled.
    return currentFrame == 9 && currentRoll >= 2 && (rolls[18] == 10 || rolls[18] + rolls[19] == 10);
}

bool BowlingGame::isStrike(const int rollIndex) const {
    return rolls[rollIndex] == 10;
}

bool BowlingGame::isSpare(const int rollIndex) const {
    return rolls[rollIndex] + rolls[rollIndex + 1] == 10;
}

int BowlingGame::strikeBonus(const int rollIndex) const {
    return rolls[rollIndex + 1] + rolls[rollIndex + 2];
}

int BowlingGame::spareBonus(const int rollIndex) const {
    return rolls[rollIndex + 2];
}

int BowlingGame::frameScore(const int rollIndex) const {
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

void BowlingGame::loadGameFromFile(const std::string& filename) {
    std::ifstream inputFile(filename);
    if (!inputFile) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }

    int pins;
    while (inputFile >> pins) {
        roll(pins);
        if (isGameOver()) {
            break;
        }
    }

    inputFile.close();
}
