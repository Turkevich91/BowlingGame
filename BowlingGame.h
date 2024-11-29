#ifndef BOWLING_GAME_H
#define BOWLING_GAME_H
#include <iostream>
#include <iomanip> // For formatting output

class BowlingGame {
public:
    BowlingGame();  // Default constructor

    // Method to register a roll
    void roll(int pins);

    // Method to get the current score
    int getScore() const;

    // Method to get the current frame number
    int getCurrentFrame() const;

    // Method to check if the game is over
    bool isGameOver() const;

    // Method to display the current score (for debugging)
    void printCurrentScore() const;

    // Method to calculate the score
    void calculateScore();

    // Indicator for whether an extra roll is allowed in the 10th frame
    bool isTenthFrameExtraRoll() const;

private:
    // Helper method to check if the current frame is a strike
    bool isStrike(int rollIndex) const;

    // Helper method to check if the current frame is a spare
    bool isSpare(int rollIndex) const;

    // Helper method to calculate the score for a strike
    int strikeBonus(int rollIndex) const;

    // Helper method to calculate the score for a spare
    int spareBonus(int rollIndex) const;

    // Helper method to calculate the score for a normal frame
    int frameScore(int rollIndex) const;

    // Array of rolls (maximum 21 rolls)
    int rolls[21] = {0};

    // Array for intermediate frame scores
    int scores[10] = {0};

    // Current roll
    int currentRoll = 0;

    // Current frame number
    int currentFrame = 0;
};

#endif // BOWLING_GAME_H