#ifndef DISCARD_PILE_H
#define DISCARD_PILE_H

#include <vector>
#include <memory>
#include <iostream>
#include "Card.h"

class CardFactory;

class DiscardPile
{
private:
    std::vector<std::unique_ptr<Card>> cards;

public:
    // Constructors
    DiscardPile() = default;
    DiscardPile(std::istream &in, const CardFactory *factory);

    // Move operations
    DiscardPile(DiscardPile &&other) noexcept = default;
    DiscardPile &operator=(DiscardPile &&other) noexcept = default;

    // Delete copy operations
    DiscardPile(const DiscardPile &) = delete;
    DiscardPile &operator=(const DiscardPile &) = delete;

    // Member functions
    DiscardPile &operator+=(std::unique_ptr<Card> card);
    std::unique_ptr<Card> pickUp();
    const Card *top() const;
    bool empty() const;
    void print(std::ostream &out) const;
    void serialize(std::ostream &out) const;

    // Destructor
    ~DiscardPile() = default;

    // Friend operator
    friend std::ostream &operator<<(std::ostream &out, const DiscardPile &pile);
};

#endif // DISCARD_PILE_H