#ifndef HAND_H
#define HAND_H

#include <list>
#include <queue>
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

    // Add card to rear of hand
    Hand &operator+=(Card *card);

    // Play and remove top card
    Card *play();

    // Get but don't remove top card
    Card *top() const;

    // Get and remove card at specific index
    Card *operator[](int index);

    // Stream insertion operator
    friend std::ostream &operator<<(std::ostream &out, const Hand &hand);

    // Destructor
    ~Hand();

    // Delete copy operations
    Hand(const Hand &) = delete;
    Hand &operator=(const Hand &) = delete;

    // Move operations
    Hand(Hand &&other) noexcept;
    Hand &operator=(Hand &&other) noexcept;

    // Additional helper methods
    bool empty() const { return cards.empty(); }
    int size() const { return cards.size(); }

    // Method to get const reference to underlying list (for viewing)
    const std::list<Card *> &getCards() const { return cards; }
    void serialize(std::ostream &out) const;

private:
    std::list<Card *> cards; // Using list for efficient random access removal

    // Helper function to serialize hand for saving to file

    // Helper to validate index
    void validateIndex(int index) const;
};

#endif // HAND_H