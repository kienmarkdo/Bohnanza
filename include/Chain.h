#ifndef CHAIN_H
#define CHAIN_H

#include "Chain_Base.h"
#include <typeinfo>

template<class T>
class Chain : public Chain_Base {
private:
    std::vector<Card*> chain;
public:
    Chain() = default;

    // Add a card to the chain
    Chain_Base& operator+=(Card* card) override {
        // Check if card is of type T using dynamic_cast
        T* casted = dynamic_cast<T*>(card);
        if (!casted) {
            throw std::invalid_argument("Attempted to add incorrect card type to chain.");
        }
        chain.push_back(card);
        return *this;
    }

    // Sell the chain
    // The logic: 
    // 1. Determine how many cards are in the chain.
    // 2. For each possible coin value (4 down to 1), check if we have enough cards to earn that many coins using card->getCardsPerCoin().
    //    We assume all cards are the same type, so just use the first card’s getCardsPerCoin.
    int sell() const override {
        if (chain.empty()) return 0;
        const Card* example = chain.front();
        int totalCards = (int)chain.size();

        // Try from 4 coins down to 1 coin
        for (int coins = 4; coins >= 1; --coins) {
            try {
                int needed = example->getCardsPerCoin(coins);
                if (totalCards >= needed) {
                    return coins;
                }
            } catch (...) {
                // If getCardsPerCoin throws, ignore and continue down
            }
        }
        return 0;
    }

    std::string getBeanName() const override {
        if (chain.empty()) {
            // If empty, we return the template type name anyway.
            T tempCard;
            return tempCard.getName();
        } else {
            return chain.front()->getName();
        }
    }

    void print(std::ostream& out) const override {
        // Print the bean name, then the cards
        // Format: "Blue  B B B ..."
        if (chain.empty()) {
            T tempCard;
            out << tempCard.getName() << " ";
        } else {
            out << chain.front()->getName() << " ";
        }

        for (auto c : chain) {
            out << *c << " ";
        }
    }

    // Optional: Could provide a way to retrieve the number of cards
    size_t size() const {
        return chain.size();
    }
};

#endif
