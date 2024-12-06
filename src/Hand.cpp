#include "Hand.h"

Hand& Hand::operator+=(Card* card) {
    cards.push_back(card);
    return *this;
}

Card* Hand::play() {
    if (cards.empty()) return nullptr;
    Card* front = cards.front();
    cards.pop_front();
    return front;
}

Card* Hand::top() const {
    if (cards.empty()) return nullptr;
    return cards.front();
}

std::ostream& operator<<(std::ostream& out, const Hand& hand) {
    if (hand.cards.empty()) {
        out << "(empty hand)";
    } else {
        for (auto c : hand.cards) {
            out << *c << " ";
        }
    }
    return out;
}
