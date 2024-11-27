#ifndef DECK_H
#define DECK_H

#include <vector>
#include <memory>
#include <iostream>
#include "Card.h"

class CardFactory;

class Deck
{
private:
    std::vector<std::unique_ptr<Card>> cards;

public:
    // Constructors
    Deck() = default;
    Deck(std::istream &in, const CardFactory *factory);

    // Move operations
    Deck(Deck &&) noexcept = default;
    Deck &operator=(Deck &&) noexcept = default;

    // Delete copy operations
    Deck(const Deck &) = delete;
    Deck &operator=(const Deck &) = delete;

    // Core functionality
    std::unique_ptr<Card> draw();
    void addCard(std::unique_ptr<Card> card);
    bool empty() const { return cards.empty(); }
    size_t size() const { return cards.size(); }

    // Serialization
    void serialize(std::ostream &out) const;
    friend std::ostream &operator<<(std::ostream &out, const Deck &deck);

    // Destructor (can be defaulted since using unique_ptr)
    ~Deck() = default;
};

#endif // DECK_H