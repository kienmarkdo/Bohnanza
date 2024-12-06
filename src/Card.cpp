#include "Card.h"
#include <stdexcept>

// Operator<< defined in Card.h via friend

// Blue
int Blue::getCardsPerCoin(int coins) const {
    switch (coins) {
        case 1: return 4;
        case 2: return 6;
        case 3: return 8;
        case 4: return 10;
        default: throw std::out_of_range("Blue: invalid coin request");
    }
}
std::string Blue::getName() const { return "Blue"; }
void Blue::print(std::ostream& out) const { out << 'B'; }

// Chili
int Chili::getCardsPerCoin(int coins) const {
    switch (coins) {
        case 1: return 3;
        case 2: return 6;
        case 3: return 8;
        case 4: return 9;
        default: throw std::out_of_range("Chili: invalid coin request");
    }
}
std::string Chili::getName() const { return "Chili"; }
void Chili::print(std::ostream& out) const { out << 'C'; }

// Stink
int Stink::getCardsPerCoin(int coins) const {
    switch (coins) {
        case 1: return 3;
        case 2: return 5;
        case 3: return 7;
        case 4: return 8;
        default: throw std::out_of_range("Stink: invalid coin request");
    }
}
std::string Stink::getName() const { return "Stink"; }
void Stink::print(std::ostream& out) const { out << 'S'; }

// Green
int Green::getCardsPerCoin(int coins) const {
    switch (coins) {
        case 1: return 3;
        case 2: return 5;
        case 3: return 6;
        case 4: return 7;
        default: throw std::out_of_range("Green: invalid coin request");
    }
}
std::string Green::getName() const { return "Green"; }
void Green::print(std::ostream& out) const { out << 'G'; }

// Soy
int Soy::getCardsPerCoin(int coins) const {
    switch (coins) {
        case 1: return 2;
        case 2: return 4;
        case 3: return 6;
        case 4: return 7;
        default: throw std::out_of_range("Soy: invalid coin request");
    }
}
std::string Soy::getName() const { return "Soy"; }
void Soy::print(std::ostream& out) const { out << 's'; } // 'S' is taken by Stink

// Black
int Black::getCardsPerCoin(int coins) const {
    switch (coins) {
        case 1: return 2;
        case 2: return 4;
        case 3: return 5;
        case 4: return 6;
        default: throw std::out_of_range("Black: invalid coin request");
    }
}
std::string Black::getName() const { return "Black"; }
void Black::print(std::ostream& out) const { out << 'b'; } // 'B' is taken by Blue

// Red
int Red::getCardsPerCoin(int coins) const {
    switch (coins) {
        case 1: return 2;
        case 2: return 3;
        case 3: return 4;
        case 4: return 5;
        default: throw std::out_of_range("Red: invalid coin request");
    }
}
std::string Red::getName() const { return "Red"; }
void Red::print(std::ostream& out) const { out << 'R'; }

// Garden
int Garden::getCardsPerCoin(int coins) const {
    // Garden does not have a valid scenario for 1 or 4 coins
    switch (coins) {
        case 2: return 2;
        case 3: return 3;
        case 1:
            throw std::out_of_range("Garden: cannot achieve 1 coin");
        case 4:
            throw std::out_of_range("Garden: cannot achieve 4 coins");
        default:
            throw std::out_of_range("Garden: invalid coin request");
    }
}
std::string Garden::getName() const { return "Garden"; }
void Garden::print(std::ostream& out) const { out << 'g'; } // 'G' used by Green
