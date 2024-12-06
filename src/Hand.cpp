#include "Hand.h"
#include "CardFactory.h"

// Constructor to load the hand from an input stream
Hand::Hand(std::istream& in, const CardFactory* factory) {
    // Load cards from input stream
}

// Add a card to the hand
Hand& Hand::operator+=(Card* card) {
    cards.push_back(card);
    return *this;
}

// Play (remove) the top card from the hand
Card* Hand::play() {
    if (cards.empty()) return nullptr;
    Card* topCard = cards.front();
    cards.pop_front();
    return topCard;
}

// Peek at the top card of the hand without removing it
Card* Hand::top() const {
    if (cards.empty()) return nullptr;
    return cards.front();
}

// Access a card by index
Card* Hand::operator[](int index) const {

    // invalid index access
    if (index < 0 || index >= static_cast<int>(cards.size())) {
        throw std::out_of_range("Invalid index for Hand");
    }


    if (index < 0 || index >= static_cast<int>(cards.size())) return nullptr;
    auto it = cards.begin();
    std::advance(it, index);
    return *it;
}

// Stream insertion operator to print the entire hand
std::ostream& operator<<(std::ostream& out, const Hand& hand) {
    for (Card* card : hand.cards) {
        out << *card << " ";
    }
    return out;
}
