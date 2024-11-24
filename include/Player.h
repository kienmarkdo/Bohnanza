#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include <memory>
#include "Hand.h"
#include "Chain.h"

// Custom exception for insufficient coins
class NotEnoughCoins : public std::exception
{
public:
    const char *what() const noexcept override
    {
        return "Not enough coins to buy third chain";
    }
};

class Player
{
public:
    // Constructor with player name
    Player(const std::string &name);

    // Constructor to reconstruct player from file
    Player(std::istream &in, const CardFactory *factory);

    // Get player's name
    std::string getName() const { return name; }

    // Get number of coins
    int getNumCoins() const { return coins; }

    // Add coins
    Player &operator+=(int additionalCoins);

    // Get maximum number of chains
    int getMaxNumChains() const { return chains.size(); }

    // Get number of non-empty chains
    int getNumChains() const;

    // Access specific chain
    Chain_Base &operator[](int i);
    const Chain_Base &operator[](int i) const;

    // Buy third chain
    void buyThirdChain();

    // Print hand
    void printHand(std::ostream &out, bool all) const;

    // Stream insertion operator
    friend std::ostream &operator<<(std::ostream &out, const Player &player);

    // Add card to hand
    void addToHand(Card *card) { hand += card; }

    // Play card from hand
    Card *playFromHand() { return hand.play(); }

    // Get specific card from hand
    Card *getCardFromHand(int index) { return hand[index]; }

    // Get top card of hand without removing
    Card *getTopCardFromHand() const { return hand.top(); }

    // Check if hand is empty
    bool isHandEmpty() const { return hand.empty(); }

    // Add a new chain of specific type
    template <typename T>
    void addChain()
    {
        if (chains.size() >= 3)
        {
            throw std::runtime_error("Maximum number of chains reached");
        }
        chains.push_back(std::make_unique<Chain<T>>());
    }
    void serialize(std::ostream &out) const;

    ~Player()
    {
        std::cout << "Player destructor start\n";
        try
        {
            std::cout << "Clearing chains first...\n";
            chains.clear(); // Clear chains first
            std::cout << "Chains cleared\n";

            std::cout << "Starting hand cleanup...\n";
            // Don't delete the hand, just let it clean up naturally
            std::cout << "Hand cleanup complete\n";
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error in Player destructor: " << e.what() << "\n";
        }
        std::cout << "Player destructor end\n";
    }

private:
    std::string name;
    int coins = 0;
    Hand hand;
    std::vector<std::unique_ptr<Chain_Base>> chains;

    // Helper function to serialize player for saving to file

    // Helper to validate chain index
    void validateChainIndex(int index) const;
};

#endif // PLAYER_H