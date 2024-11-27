#ifndef HAND_H
#define HAND_H

#include <list>
#include <memory>
#include <iostream>
#include "Card.h"

class CardFactory;

class Hand
{
public:
    // Default constructor
    Hand() = default;

    // Constructor to reconstruct hand from file
    Hand(std::istream &in, const CardFactory *factory);

    // Move operations
    Hand(Hand &&) noexcept = default;
    Hand &operator=(Hand &&) noexcept = default;

    // Delete copy operations
    Hand(const Hand &) = delete;
    Hand &operator=(const Hand &) = delete;

    // Core functionality
    Hand &operator+=(std::unique_ptr<Card> card);
    std::unique_ptr<Card> play();
    const Card *top() const;
    std::unique_ptr<Card> operator[](int index);

    // Utility methods
    bool empty() const { return cards.empty(); }
    size_t size() const { return cards.size(); }
    void serialize(std::ostream &out) const;

    // Stream operator
    friend std::ostream &operator<<(std::ostream &out, const Hand &hand);

    // View access to cards (returns const references only)
    const std::list<std::unique_ptr<Card>> &getCards() const { return cards; }

    // Destructor can be defaulted due to smart pointers
    ~Hand() = default;

private:
    std::list<std::unique_ptr<Card>> cards;
    void validateIndex(int index) const;
};

#endif // HAND_H