#ifndef DECK_H
#define DECK_H

#include <vector>
#include <iostream>
class Card;
class CardFactory;

class Deck {
private:
    std::vector<Card*> cards;
public:
    Deck() = default;
    Deck(const std::vector<Card*>& c) : cards(c) {}
    Deck(std::istream& in, CardFactory* factory);
    friend std::ostream& operator<<(std::ostream& out, const Deck& d);
    Card* draw() {
        if (cards.empty()) return nullptr;
        Card* c=cards.back(); cards.pop_back(); return c;
    }
    size_t size() const { return cards.size(); }
};

#endif
