/* Vitalii Turkevych

Bowling Game

The game consists of 10 frames as shown in the following table. The 10th frame may have up to three rolls.
This program calculates the score of a bowling game based on the number of pins knocked down in each roll.
The program uses the following rules to calculate the score:
- If a player knocks down all 10 pins with the first roll (strike), the score for that frame is 10 plus the sum of the next two rolls.
- If a player knocks down all 10 pins with two rolls (spare), the score for that frame is 10 plus the next roll.
- If a player does not knock down all 10 pins in two rolls, the score for that frame is the sum of the two rolls.
- The score for each frame is the sum of the scores of all previous frames plus the score of the current frame.
- The 10th frame may have up to three rolls if the player gets a strike or a spare.

*/





#include <iostream>
#include <iomanip> // For formatting output
using namespace std;

class Game {
private:
public:
    bool isTenthFrameExtraRoll() const { return tenthFrameExtraRoll; }

    int rolls[21];  // Array for all rolls (maximum 21 rolls)
    int scores[10]; // Array for intermediate frame scores
    int currentRoll; // Current roll
    int currentFrame; // Current frame
    bool tenthFrameExtraRoll; // Indicator if extra roll is allowed in 10th frame

public:
    Game() : currentRoll(0), currentFrame(0), tenthFrameExtraRoll(false) {
        // Initialize arrays with zeros
        for (int i = 0; i < 21; i++) rolls[i] = 0;
        for (int i = 0; i < 10; i++) scores[i] = 0;
    }

    // Method to perform a roll
    void roll(int pins) {
        rolls[currentRoll++] = pins;
        if (currentFrame < 9) { // Frames 1-9
            if (pins == 10 || currentRoll % 2 == 0) { // Strike or second roll of frame
                currentFrame++;
            }
        } else { // 10th frame special case
            if (currentRoll == 1 && pins == 10) { // Strike on first roll of 10th frame
                tenthFrameExtraRoll = true; // Allow two more rolls
            } else if (currentRoll == 2) {
                if (rolls[currentRoll - 2] == 10 || rolls[currentRoll - 2] + rolls[currentRoll - 1] == 10) {
                    tenthFrameExtraRoll = true; // Spare or second strike allows one more roll
                } else {
                    currentFrame++; // No bonus roll if less than a spare
                }
            } else if (currentRoll == 3) {
                currentFrame++; // End after third roll in the 10th frame
            }
        }
        calculateScore();  // Recalculate scores after each roll
        printScore();      // Print the results on the screen
    }

    // Method to get the current roll
    int getCurrentRoll() const {
        return currentRoll;
    }

    // Method to get the current frame
    int getFrame() const {
        return currentFrame + 1;
    }

    // Method to calculate the score
    void calculateScore() {
        int frameIndex = 0;
        for (int frame = 0; frame < 10; frame++) {
            if (rolls[frameIndex] == 10) { // Strike
                scores[frame] = 10 + rolls[frameIndex + 1] + rolls[frameIndex + 2];
                frameIndex++; // Move to the next frame
            } else if (rolls[frameIndex] + rolls[frameIndex + 1] == 10) { // Spare
                scores[frame] = 10 + rolls[frameIndex + 2];
                frameIndex += 2; // Move to the next frame
            } else { // Normal frame
                scores[frame] = rolls[frameIndex] + rolls[frameIndex + 1];
                frameIndex += 2; // Move to the next frame
            }

            // Add to previous frames
            if (frame > 0) scores[frame] += scores[frame - 1];
        }
    }

    // Method to print the results
    void printScore() const {
        constexpr int columnWidth = 5; // Set column width to 5 to accommodate up to 3 values with surrounding space

        // Line Frame
        cout << "Frame:  ";
        for (int i = 1; i <= 10; i++) {
            cout << "|" << setw(columnWidth) << i;
        }
        cout << "|" << endl;

        // Line Throw:
        cout << "Throw:  ";
        int rollIndex = 0;
        for (int frame = 0; frame < 10; frame++) {
            cout << "|";
            if (rolls[rollIndex] == 10) { // Strike
                cout << setw(columnWidth - 1) << "X";
                rollIndex++;
            } else {
                if (rollIndex < currentRoll) {
                    cout << setw(2) << rolls[rollIndex];
                } else {
                    cout << setw(columnWidth - 1) << " ";
                }
                rollIndex++;
                if (rollIndex < currentRoll) {
                    if (rolls[rollIndex - 1] + rolls[rollIndex] == 10) {
                        cout << setw(3) << "/";
                    } else {
                        cout << setw(3) << rolls[rollIndex];
                    }
                } else {
                    cout << setw(columnWidth - 2) << " ";
                }
                rollIndex++;
            }
        }
        cout << "|" << endl;

        // line Score
        cout << "Score:  ";
        for (int i = 0; i < 10; i++) {
            cout << "|" << setw(columnWidth - 1) << scores[i];
        }
        cout << "|" << endl << endl;
    }
};

int main() {
    Game game;
    int pins;

    cout << "Enter the result of each throw in order:" << endl;
    while (game.getFrame() <= 10) {
        if (game.getFrame() == 10 && game.getCurrentRoll() >= 3 && !game.isTenthFrameExtraRoll()) break; // End after third roll in the 10th frame if applicable
        cout << "Throw: ";
        cin >> pins;
        cout << endl;

        // Limit the number of pins knocked down (maximum 10 per roll)
        if (pins < 0 || pins > 10) {
            cout << "Invalid input. Please enter a value between 0 and 10." << endl;
            continue;
        }

        game.roll(pins);
    }

    return 0;
}
