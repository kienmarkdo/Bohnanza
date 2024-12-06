#ifndef HAND_H
#define HAND_H

#include <list>
#include <iostream>
#include "Card.h"

class Hand {
private:
    std::list<Card*> cards;
public:
    Hand() = default;

    // Add a card to the back of the hand
    Hand& operator+=(Card* card);

    // Returns and removes the front card of the hand
    Card* play();

    // Returns the front card without removing it
    Card* top() const;

    // Check if empty
    bool isEmpty() const { return cards.empty(); }

    // Print hand: front to back
    friend std::ostream& operator<<(std::ostream& out, const Hand& hand);
};

#endif
