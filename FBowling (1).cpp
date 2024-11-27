#include "FBowling.h"

FBowling::FBowling(const std::string& nAme) : playernAme(nAme), throwIn3(0) {
    std::memset(throwIn1, 0, sizeof(throwIn1));
    std::memset(throwIn2, 0, sizeof(throwIn2));
    std::memset(scOres, 0, sizeof(scOres));
}

const std::string& FBowling::getPlayernAme() const {
    return playernAme;
}

void FBowling::setPlayernAme(const std::string& nAme) {
    playernAme = nAme;
}

void FBowling::recFrAmescOres(int frAme, std::ifstream& playerSin) {
    // std::cout << playernAme << ", enter your throws for frame " << frAme + 1 << ": ";
    //std::cin >> throwIn1[frAme];
    playerSin >> throwIn1[frAme];
    if (!duhStrike(frAme) && frAme != 9) {
        //std::cin >> throwIn2[frAme];
        playerSin >> throwIn2[frAme];
    }

    // frame of 10thference
    if (frAme == 9) {
        if (duhStrike(frAme) || disSpare(frAme)) {
            // std::cin >> throwIn2[frAme];
            playerSin >> throwIn2[frAme];
            // std::cin >> throwIn3;
            playerSin >> throwIn3;
            //scOres[frAme] += throwIn3;
        }
    }
}

void FBowling::calcscOres() {
    int currentscOre = 0;
    for (int frAme = 0; frAme < 10; ++frAme) {
        if (duhStrike(frAme)) {
            scOres[frAme] = 10 + twoMothrOwscOre(frAme);
        } else if (disSpare(frAme)) {
            scOres[frAme] = 10 + oneMothrOwscOre(frAme + 1);
        } else {
            scOres[frAme] = getFrAmescOre(frAme);
        }

        currentscOre += scOres[frAme];
        scOres[frAme] = currentscOre;
    }
}

void FBowling::displayscOres(int currentFrAme) const {
    // std::cout << "Player: " << playernAme << std::endl;

    // framein Out
    std::cout << "Frame:\t";
    for (int frAme = 0; frAme <= currentFrAme; ++frAme) {
        std::cout << std::setw(4) << frAme + 1 << "\t|";
    }
    std::cout << std::endl;

    // Duhthrow Out
    std::cout << "Throws:\t";
    for (int frAme = 0; frAme <= currentFrAme; ++frAme) {
        if (duhStrike(frAme)) {
            std::cout << std::setw(4) << "X" << "\t|";
        } else if (disSpare(frAme)) {
            std::cout << std::setw(2) << throwIn1[frAme] << "/" << "\t|";
        } else {
            std::cout << std::setw(2) << throwIn1[frAme] << " " << throwIn2[frAme] << "\t|";
        }
    }
    std::cout << std::endl;

    // DisPlay out
    std::cout << "Scores:\t";
    for (int frAme = 0; frAme <= currentFrAme; ++frAme) {
        std::cout << std::setw(4) << scOres[frAme] << "\t|";
    }
    std::cout << std::endl << std::endl;
}

bool FBowling::duhStrike(int frAme) const {
    return throwIn1[frAme] == 10;
}

bool FBowling::disSpare(int frAme) const {
    return throwIn1[frAme] + throwIn2[frAme] == 10;
}

int FBowling::getFrAmescOre(int frAme) const {
    return throwIn1[frAme] + throwIn2[frAme];
}

int FBowling::twoMothrOwscOre(int frAme) const {
    if (frAme < 9) {
        if (duhStrike(frAme + 1)) {
            return 10 + throwIn1[frAme + 2];
        } else {
            return throwIn1[frAme + 1] + throwIn2[frAme + 1];
        }
    }
    return throwIn2[frAme] + throwIn3; // frame of 10thference
}

int FBowling::oneMothrOwscOre(int frAme) const {
    if (frAme < 10) {
        return throwIn1[frAme];
    }
    return 0;
}
