#ifndef HAND_H
#define HAND_H

#include <list>
#include <iostream>
#include "Card.h"

/**
 * @class Hand
 * @brief Represents a player's hand of cards.
 * 
 * Cards are held in order and can be drawn from the front.
 * The insertion is always at the back.
 */
class Hand {
private:
    std::list<Card*> cards;
public:
    Hand() = default;

    /**
     * @brief Add a card to the back of the hand.
     */
    Hand& operator+=(Card* card);

    /**
     * @brief Removes and returns the front card of the hand.
     * @return The front card, or nullptr if empty.
     */
    Card* play();

    /**
     * @brief Returns the front card without removing it.
     * @return The front card, or nullptr if empty.
     */
    Card* top() const;

    /**
     * @brief Check if the hand is empty.
     * @return true if empty, false otherwise.
     */
    bool isEmpty() const { return cards.empty(); }

    /**
     * @brief Print all cards in the hand from front to back.
     */
    friend std::ostream& operator<<(std::ostream& out, const Hand& hand);
};

#endif
