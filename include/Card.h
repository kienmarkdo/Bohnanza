#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>
using namespace std; // Using this globally for simplicity in this project

/**
 * Abstract base class for Card
 * Represents a general card in the game with basic functionality to retrieve its name,
 * print its representation, and determine cards needed for coin levels.
 */
class Card {
public:
    /**
     * Pure virtual method to get the number of cards required to earn a specific number of coins.
     * @param coins The number of coins to check.
     * @return Number of cards required.
     */
    virtual int getCardsPerCoin(int coins) const = 0;

    /**
     * Pure virtual method to get the name of the card.
     * @return Name of the card as a string.
     */
    virtual string getName() const = 0;

    /**
     * Pure virtual method to print the card's representation.
     * @param out Output stream to print to.
     */
    virtual void print(ostream& out) const = 0;

    /// Virtual destructor for proper cleanup in derived classes.
    virtual ~Card() = default;
};

/**
 * Represents a Blue card in the game.
 */
class Blue : public Card {
public:
    int getCardsPerCoin(int coins) const override;
    string getName() const override;
    void print(ostream& out) const override;
};

/**
 * Represents a Chili card in the game.
 */
class Chili : public Card {
public:
    int getCardsPerCoin(int coins) const override;
    string getName() const override;
    void print(ostream& out) const override;
};

/**
 * Represents a Stink card in the game.
 */
class Stink : public Card {
public:
    int getCardsPerCoin(int coins) const override;
    string getName() const override;
    void print(ostream& out) const override;
};

/**
 * Represents a Green card in the game.
 */
class Green : public Card {
public:
    int getCardsPerCoin(int coins) const override;
    string getName() const override;
    void print(ostream& out) const override;
};

/**
 * Represents a soy card in the game.
 */
class soy : public Card {
public:
    int getCardsPerCoin(int coins) const override;
    string getName() const override;
    void print(ostream& out) const override;
};

/**
 * Represents a black card in the game.
 */
class black : public Card {
public:
    int getCardsPerCoin(int coins) const override;
    string getName() const override;
    void print(ostream& out) const override;
};

/**
 * Represents a Red card in the game.
 */
class Red : public Card {
public:
    int getCardsPerCoin(int coins) const override;
    string getName() const override;
    void print(ostream& out) const override;
};

/**
 * Represents a garden card in the game.
 */
class garden : public Card {
public:
    int getCardsPerCoin(int coins) const override;
    string getName() const override;
    void print(ostream& out) const override;
};

#endif
