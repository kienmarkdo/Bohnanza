#ifndef HAND_H
#define HAND_H

#include <list>
#include <iostream>
class Card;
class CardFactory;

class Hand {
private:
    std::list<Card*> cards;
public:
    Hand() = default;
    Hand(std::istream& in, CardFactory* factory);
    friend std::ostream& operator<<(std::ostream& out, const Hand& h);
    Hand& operator+=(Card* c) { cards.push_back(c); return *this; }
    Card* play() {
        if (cards.empty()) return nullptr;
        Card* c=cards.front(); cards.pop_front(); return c;
    }
    Card* top() const {
        if (cards.empty()) return nullptr;
        return cards.front();
    }
};

#endif
