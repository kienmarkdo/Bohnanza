#ifndef DECK_H
#define DECK_H

#include <vector>
#include <algorithm>
#include <random>
#include <iostream>
#include "Card.h"
#include "CardFactory.h"

class Deck : public std::vector<Card *>
{
public:
    // Constructor to initialize the Deck with all cards
    Deck();
    Deck(const std::vector<Card *> &cards);

    // Constructor to reconstruct the Deck from a file
    Deck(std::istream &in, const CardFactory *factory);

    // Shuffles the Deck
    void shuffle();

    // Draws the top card from the Deck
    Card *draw();

    // Prints all cards in the Deck
    friend std::ostream &operator<<(std::ostream &out, const Deck &deck);
};

#endif // DECK_H