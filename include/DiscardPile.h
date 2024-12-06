#ifndef DISCARDPILE_H
#define DISCARDPILE_H

#include <vector>
#include <iostream>
class Card;
class CardFactory;

class DiscardPile {
private:
    std::vector<Card*> pile;
public:
    DiscardPile() = default;
    DiscardPile(std::istream& in, CardFactory* factory);
    friend std::ostream& operator<<(std::ostream& out, const DiscardPile& dp);
    DiscardPile& operator+=(Card* c) { pile.push_back(c); return *this; }
    Card* pickUp() {
        if (pile.empty()) return nullptr;
        Card* c = pile.back(); pile.pop_back(); return c;
    }
    Card* top() const {
        if (pile.empty()) return nullptr;
        return pile.back();
    }
};

#endif
