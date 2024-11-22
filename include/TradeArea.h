#ifndef TRADEAREA_H
#define TRADEAREA_H

#include <list>
#include <string>
#include <iostream>
#include "Card.h"
#include "CardFactory.h"

class TradeArea
{
private:
    // List to hold the cards
    std::list<Card *> cards;

public:
    TradeArea();
    // Constructor to reconstruct the TradeArea from a file
    TradeArea(std::istream &in, const CardFactory *factory);

    // Adds a card to the TradeArea
    TradeArea &operator+=(Card *card);

    // Checks if the card can be legally added to the TradeArea
    bool legal(Card *card) const;

    // Removes and returns a card of the specified bean name
    Card *trade(const std::string &beanName);

    // Returns the number of cards in the TradeArea
    int numCards() const;

    // Stream insertion operator to print all cards in the TradeArea
    friend std::ostream &operator<<(std::ostream &out, const TradeArea &tradeArea);
};

#endif // TRADEAREA_H