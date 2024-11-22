#ifndef DISCARDPILE_H
#define DISCARDPILE_H

#include <vector>
#include <iostream>
#include "Card.h"
#include "CardFactory.h"

class DiscardPile
{
private:
    // Vector to store cards
    std::vector<Card *> pile;

public:
    DiscardPile();
    // Constructor to reconstruct the DiscardPile from a file
    DiscardPile(std::istream &in, const CardFactory *factory);

    // Discard a card to the pile
    DiscardPile &operator+=(Card *card);

    // Remove and return the top card from the pile
    Card *pickUp();

    // Return but do not remove the top card
    Card *top() const;

    // Print all cards in the DiscardPile
    void print(std::ostream &out) const;

    // Stream insertion operator to insert only the top card
    friend std::ostream &operator<<(std::ostream &out, const DiscardPile &discardPile);
};

#endif // DISCARDPILE_H