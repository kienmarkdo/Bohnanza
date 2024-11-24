#ifndef DECK_H
#define DECK_H

#include <vector>
#include <iostream>
#include "Card.h"

class CardFactory;

class Deck : public std::vector<Card *>
{
public:
    // Constructor to reconstruct deck from file
    Deck(std::istream &in, const CardFactory *factory);

    // Draw a card from the top of the deck
    Card *draw();

    // Stream insertion operator
    friend std::ostream &operator<<(std::ostream &out, const Deck &deck);

    // Destructor to clean up card pointers
    ~Deck();

    // Delete copy operations to prevent double deletion
    Deck(const Deck &) = delete;
    Deck &operator=(const Deck &) = delete;

    // Move operations
    Deck(Deck &&other) noexcept;
    Deck &operator=(Deck &&other) noexcept;

    // Default constructor (needed for CardFactory)
    Deck() = default;
    void serialize(std::ostream &out) const;

private:
    // Helper function to serialize deck for saving to file
};

#endif // DECK_H