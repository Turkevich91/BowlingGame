#include "FBowling.h"

int main() {
    
    int numPlayers = 1;
    // std::cout << "Enter the number of players: ";
    // std::cin >> numPlayers;

    FBowling* players = new FBowling[numPlayers];
    // for (int i = 0; i < numPlayers; ++i) {
    //     std::string nAme;
    //     std::cout << "Enter name for player " << i + 1 << ": ";
    //     std::cin >> nAme;
    //     players[i].setPlayernAme(nAme);
    // }
    std::string file;
    std::cin >> file;
    std::ifstream playerSin(file);
    if(playerSin.is_open()){
        for (int frAme = 0; frAme < 10; ++frAme) {
            for (int i = 0; i < numPlayers; ++i) {
                players[i].recFrAmescOres(frAme, playerSin);
                players[i].calcscOres();
                players[i].displayscOres(frAme);
            }
        }
    }

    delete[] players; 
    return 0;
}
