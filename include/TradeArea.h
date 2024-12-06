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
    friend std::ostream& operator<<(std::ostream& out, const TradeArea& tradeArea);

private:
    std::list<Card*> tradeCards;
};

#endif // TRADEAREA_H
