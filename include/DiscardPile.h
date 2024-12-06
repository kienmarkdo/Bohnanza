#ifndef DISCARDPILE_H
#define DISCARDPILE_H

#include <vector>
#include <iostream>
#include "Card.h"

class DiscardPile {
private:
    std::vector<Card*> pile;
public:
    DiscardPile() = default;

    // Add a card to the top of the discard pile
    DiscardPile& operator+=(Card* card);

    // Take a card from the top of the discard pile
    // Returns nullptr if empty
    Card* pickUp();

    // Return the top card without removing it
    Card* top() const;

    // Check if a given bean card is in the pile
    bool isEmpty() const { return pile.empty(); }

    // Print all cards (top to bottom)
    friend std::ostream& operator<<(std::ostream& out, const DiscardPile& dp);
};

#endif
