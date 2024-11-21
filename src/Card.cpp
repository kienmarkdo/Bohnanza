#include "Card.h"

// ========================
// Implementation for Blue
// ========================

/**
 * Determines the number of Blue cards needed to earn the specified number of coins.
 * @param coins The number of coins to check.
 * @return Number of Blue cards required.
 */
int Blue::getCardsPerCoin(int coins) const {
    if (coins == 1) return 4;
    if (coins == 2) return 6;
    if (coins == 3) return 8;
    if (coins == 4) return 10;
    return -1; // Invalid value. Can't get 0 coins, or 5 coins or more.
}

/**
 * Retrieves the name of the Blue card.
 * @return "Blue" as the name of the card.
 */
string Blue::getName() const {
    return "Blue";
}

/**
 * Prints the representation of the Blue card to the output stream.
 * @param out Output stream to print to.
 */
void Blue::print(ostream& out) const {
    out << "B"; // Represents Blue card as "B"
}

// =========================
// Implementation for Chili
// =========================

/**
 * Determines the number of Chili cards needed to earn the specified number of coins.
 * @param coins The number of coins to check.
 * @return Number of Chili cards required.
 */
int Chili::getCardsPerCoin(int coins) const {
    if (coins == 1) return 3;
    if (coins == 2) return 6;
    if (coins == 3) return 8;
    if (coins == 4) return 9;
    return -1; // Invalid value. Can't get 0 coins, or 5 coins or more.
}

/**
 * Retrieves the name of the Chili card.
 * @return "Chili" as the name of the card.
 */
string Chili::getName() const {
    return "Chili";
}

/**
 * Prints the representation of the Chili card to the output stream.
 * @param out Output stream to print to.
 */
void Chili::print(ostream& out) const {
    out << "C"; // Represents Chili card as "C"
}

// =========================
// Implementation for Stink
// =========================

/**
 * Determines the number of Stink cards needed to earn the specified number of coins.
 * @param coins The number of coins to check.
 * @return Number of Stink cards required.
 */
int Stink::getCardsPerCoin(int coins) const {
    if (coins == 1) return 3;
    if (coins == 2) return 5;
    if (coins == 3) return 7;
    if (coins == 4) return 8;
    return -1; // Invalid value. Can't get 0 coins, or 5 coins or more.
}

/**
 * Retrieves the name of the Stink card.
 * @return "Stink" as the name of the card.
 */
string Stink::getName() const {
    return "Stink";
}

/**
 * Prints the representation of the Stink card to the output stream.
 * @param out Output stream to print to.
 */
void Chili::print(ostream& out) const {
    out << "S"; // Represents Stink card as "C"
}

// =========================
// Implementation for Green
// =========================

/**
 * Determines the number of Green cards needed to earn the specified number of coins.
 * @param coins The number of coins to check.
 * @return Number of Green cards required.
 */
int Green::getCardsPerCoin(int coins) const {
    if (coins == 1) return 3;
    if (coins == 2) return 5;
    if (coins == 3) return 6;
    if (coins == 4) return 7;
    return -1; // Invalid value. Can't get 0 coins, or 5 coins or more.
}

/**
 * Retrieves the name of the Green card.
 * @return "Green" as the name of the card.
 */
string Green::getName() const {
    return "Green";
}

/**
 * Prints the representation of the Green card to the output stream.
 * @param out Output stream to print to.
 */
void Chili::print(ostream& out) const {
    out << "G";
}

// =========================
// Implementation for soy
// =========================

/**
 * Determines the number of soy cards needed to earn the specified number of coins.
 * @param coins The number of coins to check.
 * @return Number of soy cards required.
 */
int soy::getCardsPerCoin(int coins) const {
    if (coins == 1) return 2;
    if (coins == 2) return 4;
    if (coins == 3) return 6;
    if (coins == 4) return 7;
    return -1; // Invalid value. Can't get 0 coins, or 5 coins or more.
}

/**
 * Retrieves the name of the soy card.
 * @return "soy" as the name of the card.
 */
string soy::getName() const {
    return "soy";
}

/**
 * Prints the representation of the soy card to the output stream.
 * @param out Output stream to print to.
 */
void Chili::print(ostream& out) const {
    out << "s";
}

// =========================
// Implementation for black
// =========================

/**
 * Determines the number of black cards needed to earn the specified number of coins.
 * @param coins The number of coins to check.
 * @return Number of black cards required.
 */
int black::getCardsPerCoin(int coins) const {
    if (coins == 1) return 2;
    if (coins == 2) return 4;
    if (coins == 3) return 5;
    if (coins == 4) return 6;
    return -1; // Invalid value. Can't get 0 coins, or 5 coins or more.
}

/**
 * Retrieves the name of the black card.
 * @return "black" as the name of the card.
 */
string black::getName() const {
    return "black";
}

/**
 * Prints the representation of the black card to the output stream.
 * @param out Output stream to print to.
 */
void Chili::print(ostream& out) const {
    out << "b";
}

// =========================
// Implementation for Red
// =========================

/**
 * Determines the number of Red cards needed to earn the specified number of coins.
 * @param coins The number of coins to check.
 * @return Number of Red cards required.
 */
int Red::getCardsPerCoin(int coins) const {
    if (coins == 1) return 2;
    if (coins == 2) return 3;
    if (coins == 3) return 4;
    if (coins == 4) return 5;
    return -1; // Invalid value. Can't get 0 coins, or 5 coins or more.
}

/**
 * Retrieves the name of the Red card.
 * @return "Red" as the name of the card.
 */
string Red::getName() const {
    return "Red";
}

/**
 * Prints the representation of the Red card to the output stream.
 * @param out Output stream to print to.
 */
void Chili::print(ostream& out) const {
    out << "R";
}

// =========================
// Implementation for garden
// =========================

/**
 * Determines the number of garden cards needed to earn the specified number of coins.
 * @param coins The number of coins to check.
 * @return Number of garden cards required.
 */
int garden::getCardsPerCoin(int coins) const {
    if (coins == 1) return 0;
    if (coins == 2) return 2;
    if (coins == 3) return 3;
    if (coins == 4) return 0;
    return -1; // Invalid value. Can't get 0 coins, or 5 coins or more.
}

/**
 * Retrieves the name of the garden card.
 * @return "garden" as the name of the card.
 */
string garden::getName() const {
    return "garden";
}

/**
 * Prints the representation of the garden card to the output stream.
 * @param out Output stream to print to.
 */
void Chili::print(ostream& out) const {
    out << "g";
}