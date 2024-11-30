#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include <memory>
#include "Hand.h"
#include "Chain.h"

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
    // Constructors
    Player(const std::string &name);
    Player(std::istream &in, const CardFactory *factory);

    // Getters
    std::string getName() const { return name; }
    int getNumCoins() const { return coins; }
    int getMaxNumChains() const { return (chains.size() >= 3) ? 3 : 2; }
    int getNumChains() const;

    // Chain operations
    Chain_Base &operator[](int i);
    const Chain_Base &operator[](int i) const;
    void buyThirdChain();

    // Hand operations
    void addToHand(std::unique_ptr<Card> card) { hand += std::move(card); }
    std::unique_ptr<Card> playFromHand() { return hand.play(); }
    std::unique_ptr<Card> getCardFromHand(int index) { return hand[index]; }
    const Card *getTopCardFromHand() const { return hand.top(); }
    bool isHandEmpty() const { return hand.empty(); }
    void addToFrontOfHand(std::unique_ptr<Card> card);
    // Coin operations
    Player &operator+=(int additionalCoins);

    // Chain management

    template <typename T>
    Chain<T> *findChainOfType()
    {
        for (auto &chain : chains)
        {
            if (chain)
            {
                if (auto typedChain = dynamic_cast<Chain<T> *>(chain.get()))
                {
                    return typedChain;
                }
            }
        }
        return nullptr;
    }

    template <typename T>
    Chain<T> &addCardToChain(std::unique_ptr<Card> card)
    {
        // First try to find an existing chain of this type
        if (auto existingChain = findChainOfType<T>())
        {
            *existingChain += std::move(card);
            return *existingChain;
        }

        // No existing chain found, look for first empty slot
        for (auto &chain : chains)
        {
            if (!chain)
            {
                chain = std::make_unique<Chain<T>>();
                *chain += std::move(card);
                return *dynamic_cast<Chain<T> *>(chain.get());
            }
        }
        throw std::runtime_error("No available chain slots");
    }

    // Display methods
    void printHand(std::ostream &out, bool all) const;
    void serialize(std::ostream &out) const;
    friend std::ostream &operator<<(std::ostream &out, const Player &player);

    // Destructor can be defaulted since using smart pointers
    ~Player() = default;

private:
    std::string name;
    int coins = 0;
    Hand hand;
    std::vector<std::unique_ptr<Chain_Base>> chains;

    void validateChainIndex(int index) const;
};

#endif // PLAYER_H