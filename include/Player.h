#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include <iostream>
#include "Chain_Base.h"
#include "Hand.h"
#include "Chain.h"
#include "Card.h"

/**
 * @class Player
 * @brief Represents a player with a name, coins, chains, and a hand of cards.
 */
class Player {
private:
    std::string name;
    int coins;
    std::vector<Chain_Base*> chains;
    Hand hand;
    int maxChains; // Typically 2, can be increased to 3

public:
    /**
     * @brief Construct a player with a given name.
     */
    Player(const std::string& playerName);

    /**
     * @brief Get the player's name.
     */
    std::string getName() const;

    /**
     * @brief Get how many coins the player has.
     */
    int getNumCoins() const;

    /**
     * @brief Add coins to the player's total.
     */
    void addCoins(int c);

    /**
     * @brief Attempt to buy a third chain for 2 coins.
     * @return true if successful, false otherwise.
     */
    bool buyThirdChain();

    /**
     * @brief Get maximum number of chains (2 or 3).
     */
    int getMaxNumChains() const;

    /**
     * @brief Get current number of chains.
     */
    int getNumChains() const;

    /**
     * @brief Access a chain by index.
     */
    Chain_Base& operator[](int i);

    /**
     * @brief Create a chain of a specific bean type (template).
     */
    template<class T>
    void createChain() {
        if ((int)chains.size() < maxChains) {
            chains.push_back(new Chain<T>());
        } else {
            throw std::runtime_error("No more chains can be created.");
        }
    }

    /**
     * @brief Add a card to the player's hand.
     */
    Player& operator+=(Card* card);

    /**
     * @brief Remove and return the top card from the player's hand.
     */
    Card* playCard();

    /**
     * @brief View the top card without removing it.
     */
    Card* topCard() const;

    /**
     * @brief Get a const reference to the player's hand for printing.
     */
    const Hand& getHand() const { return hand; }

    /**
     * @brief Print the player status to an ostream.
     */
    friend std::ostream& operator<<(std::ostream& out, const Player& player);

    ~Player();
};

#endif
