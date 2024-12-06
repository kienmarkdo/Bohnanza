#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include <iostream>
#include "Chain_Base.h"
#include "Hand.h"
#include "Chain.h" // to instantiate chains
#include "Card.h"

class Player {
private:
    std::string name;
    int coins;
    std::vector<Chain_Base*> chains;
    Hand hand;
    int maxChains; // Typically 2, can be increased to 3

public:
    Player(const std::string& playerName);

    // Returns player's name
    std::string getName() const;

    // How many coins does player have
    int getNumCoins() const;

    // Add coins
    void addCoins(int c);

    // Buy a third chain for 2 coins (if allowed)
    bool buyThirdChain();

    // How many chains does player have
    int getMaxNumChains() const;

    int getNumChains() const;

    // Access to a chain
    Chain_Base& operator[](int i);

    // Add a chain of a given type T if needed
    template<class T>
    void createChain() {
        if ((int)chains.size() < maxChains) {
            chains.push_back(new Chain<T>());
        } else {
            throw std::runtime_error("No more chains can be created.");
        }
    }

    // Add a card to player's hand
    Player& operator+=(Card* card);

    // Take the top card from player's hand
    Card* playCard();

    // Return the top card
    Card* topCard() const;

    // Print player:
    // Format: prints player’s name, coins, and each chain on its own line.
    friend std::ostream& operator<<(std::ostream& out, const Player& player);

    ~Player();
};

#endif
