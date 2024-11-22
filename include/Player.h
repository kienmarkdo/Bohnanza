#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include <iostream>
#include "Chain.h"
#include "Hand.h"
#include "CardFactory.h"

class Player
{
private:
    std::string name;                 // Name of the player
    int coins;                        // Number of coins the player has
    std::vector<Chain_Base *> chains; // Chains owned by the player
    Hand hand;                        // Player's hand
    int maxChains;                    // Maximum number of chains (2 or 3)

public:
    // Constructor: Creates a Player with a given name
    Player(const std::string &playerName);

    // Constructor: Reconstructs a Player from a file
    Player(std::istream &in, const CardFactory *factory);

    // Get the name of the player
    std::string getName() const;

    // Get the number of coins
    int getNumCoins() const;

    // Add coins to the player
    Player &operator+=(int numCoins);

    // Get the maximum number of chains
    int getMaxNumChains() const;

    // Get the number of non-empty chains
    int getNumChains() const;

    // Access the chain at position i
    Chain_Base &operator[](int i);

    // Buy a third chain (reduces coins, throws exception if not enough coins)
    void buyThirdChain();

    // Print the player's hand
    void printHand(std::ostream &out, bool showAll) const;

    // Stream insertion operator to print a Player
    friend std::ostream &operator<<(std::ostream &out, const Player &player);
};

#endif // PLAYER_H