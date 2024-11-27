#ifndef FBOWLING_H
#define FBOWLING_H

#include <string>
#include <iostream>
#include <iomanip>
#include <cstring> // memset
#include <fstream>

class FBowling {
private:
    std::string playernAme;
    int throwIn1[10];   // throw 1
    int throwIn2[10];   // throw 2
    int throwIn3;       // 3rd 10thference
    int scOres[10];   // scorin' frames

public:
    FBowling(const std::string& nAme = "");
    const std::string& getPlayernAme() const;
    void setPlayernAme(const std::string& nAme);
    void currentscOres();
    void recFrAmescOres(int frAme, std::ifstream& playerSin);
    void calcscOres();
    void displayscOres(int currentFrAme) const;

private:
    bool duhStrike(int frAme) const;
    bool disSpare(int frAme) const;
    int getFrAmescOre(int frAme) const;
    int twoMothrOwscOre(int frAme) const;
    int oneMothrOwscOre(int frAme) const;
};

#endif
