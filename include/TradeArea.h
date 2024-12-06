#ifndef TRADEAREA_H
#define TRADEAREA_H

#include <list>
#include <iostream>

#include "Card.h"
#include "CardFactory.h"


class TradeArea {
public:
    TradeArea();
    TradeArea& operator+=(Card* card);
    bool legal(Card* card) const;
    Card* trade(const std::string& cardName);
    bool isEmpty() const;
    const std::list<Card*>& getCards() const;
    void clear();

    friend std::ostream& operator<<(std::ostream& out, const TradeArea& tradeArea);
    friend std::istream& operator>>(std::istream& in, TradeArea& tradeArea);


private:
    std::list<Card*> tradeCards;
};

#endif // TRADEAREA_H
