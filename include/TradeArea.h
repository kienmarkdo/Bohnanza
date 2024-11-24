#ifndef TRADE_AREA_H
#define TRADE_AREA_H

#include <list>
#include <string>
#include <iostream>
#include "Card.h"

class CardFactory;

class TradeArea
{
public:
    // Default constructor
    TradeArea() = default;

    // Constructor to reconstruct trade area from file
    TradeArea(std::istream &in, const CardFactory *factory);

    // Add card to trade area
    TradeArea &operator+=(Card *card);

    // Check if card can be legally added
    bool legal(Card *card) const;

    // Remove and return a card of given bean name
    Card *trade(const std::string &bean);

    // Get number of cards in trade area
    int numCards() const { return cards.size(); }

    // Stream insertion operator
    friend std::ostream &operator<<(std::ostream &out, const TradeArea &tradeArea);

    // Destructor
    ~TradeArea();

    // Delete copy operations
    TradeArea(const TradeArea &) = delete;
    TradeArea &operator=(const TradeArea &) = delete;

    // Move operations
    TradeArea(TradeArea &&other) noexcept;
    TradeArea &operator=(TradeArea &&other) noexcept;

    // Additional helper methods
    bool empty() const { return cards.empty(); }
    bool contains(const std::string &beanName) const;

    // Iterator access for external traversal
    using iterator = std::list<Card *>::iterator;
    using const_iterator = std::list<Card *>::const_iterator;

    iterator begin() { return cards.begin(); }
    iterator end() { return cards.end(); }
    const_iterator begin() const { return cards.begin(); }
    const_iterator end() const { return cards.end(); }
    const_iterator cbegin() const { return cards.cbegin(); }
    const_iterator cend() const { return cards.cend(); }
    void serialize(std::ostream &out) const;

private:
    std::list<Card *> cards;

    // Helper function to serialize trade area for saving to file
};

#endif // TRADE_AREA_H