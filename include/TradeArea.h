#ifndef TRADEAREA_H
#define TRADEAREA_H

#include <list>
#include <iostream>
#include "Card.h"

class TradeArea {
private:
    std::list<Card*> cards;
public:
    TradeArea() = default;

    // Add a card to the TradeArea
    TradeArea& operator+=(Card* card);

    // Check if card of this bean type is in the trade area
    bool legal(Card* card) const;

    // Remove and return a card of the specified bean name if present
    Card* trade(const std::string& beanName);

    // Number of cards in TradeArea
    int numCards() const { return (int)cards.size(); }

    friend std::ostream& operator<<(std::ostream& out, const TradeArea& ta);
};

#endif
