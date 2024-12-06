#ifndef DECK_H
#define DECK_H

#include <vector>
#include <iostream>
#include "Card.h"

class Deck {
private:
    std::vector<Card*> cards;
public:
    Deck() = default;
    Deck(const std::vector<Card*>& cardList) : cards(cardList) {}

    // Draws the top card from the deck and returns it, removing it from the deck
    // If empty, returns nullptr or throws an exception
    Card* draw() {
        if (cards.empty()) {
            return nullptr;
        }
        Card* top = cards.back();
        cards.pop_back();
        return top;
    }

    // Returns the number of cards left in the deck
    size_t size() const {
        return cards.size();
    }

    // Insert a card at the bottom of the deck (front)
    void push_front(Card* c) {
        cards.insert(cards.begin(), c);
    }

    // Print deck: print all cards from top to bottom or bottom to top as needed.
    // Typically for debugging: print top at the rightmost side.
    friend std::ostream& operator<<(std::ostream& out, const Deck& deck) {
        for (auto c : deck.cards) {
            out << *c << " ";
        }
        return out;
    }
};

#endif
