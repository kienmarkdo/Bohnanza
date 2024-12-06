#ifndef TRADEAREA_H
#define TRADEAREA_H

#include <list>
#include <iostream>
#include <string>
#include "Card.h"
class CardFactory;

class TradeArea {
private:
    std::list<Card*> cards;
public:
    TradeArea() = default;
    TradeArea(std::istream& in, CardFactory* factory);
    friend std::ostream& operator<<(std::ostream& out, const TradeArea& ta);
    TradeArea& operator+=(Card* c) { cards.push_back(c); return *this; }
    bool legal(Card* c) const {
        if (cards.empty()) return true;
        std::string n = c->getName();
        for (auto x: cards) if (x->getName()==n) return true;
        return false;
    }
};

#endif
