#ifndef DISCARD_PILE_H
#define DISCARD_PILE_H

#include <vector>
#include <iostream>
#include "Card.h"

class CardFactory;

class DiscardPile
{
public:
    // Default constructor
    DiscardPile() = default;

    // Constructor to reconstruct discard pile from file
    DiscardPile(std::istream &in, const CardFactory *factory);

    // Add card to the pile
    DiscardPile &operator+=(Card *card);

    // Pick up and remove top card
    Card *pickUp();

    // View top card without removing
    Card *top() const;

    // Print all cards in the pile
    void print(std::ostream &out) const;

    // Stream insertion operator (prints only top card)
    friend std::ostream &operator<<(std::ostream &out, const DiscardPile &pile);

    // Destructor
    ~DiscardPile();
    void deserialize(std::istream &in, const CardFactory *factory);

    // Delete copy operations
    DiscardPile(const DiscardPile &) = delete;
    DiscardPile &operator=(const DiscardPile &) = delete;

    // Move operations
    DiscardPile(DiscardPile &&other) noexcept;
    DiscardPile &operator=(DiscardPile &&other) noexcept;

    // Additional helper methods
    bool empty() const { return cards.empty(); }
    size_t size() const { return cards.size(); }
    void serialize(std::ostream &out) const;

private:
    std::vector<Card *> cards;
};

#endif // DISCARD_PILE_H