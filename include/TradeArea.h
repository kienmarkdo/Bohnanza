#ifndef TRADE_AREA_H
#define TRADE_AREA_H

#include <vector>
#include <memory>
#include <iostream>
#include "Card.h"

class CardFactory;

class TradeArea
{
private:
    std::vector<std::unique_ptr<Card>> cards;

public:
    // Constructors
    TradeArea() = default;
    TradeArea(std::istream &in, const CardFactory *factory);

    // Move operations
    TradeArea(TradeArea &&) noexcept = default;
    TradeArea &operator=(TradeArea &&) noexcept = default;

    // Delete copy operations
    TradeArea(const TradeArea &) = delete;
    TradeArea &operator=(const TradeArea &) = delete;

    // Core functionality
    TradeArea &operator+=(std::unique_ptr<Card> card);
    bool legal(const Card *card) const;
    std::unique_ptr<Card> trade(const std::string &bean);
    bool contains(const std::string &beanName) const;
    void removeIllegalCards();
    // Additional utility methods
    bool empty() const { return cards.empty(); }
    size_t numCards() const { return cards.size(); }

    // Begin and end for range-based for loop
    auto begin() const { return cards.begin(); }
    auto end() const { return cards.end(); }

    // Serialization
    void serialize(std::ostream &out) const;
    friend std::ostream &operator<<(std::ostream &out, const TradeArea &tradeArea);

    // Destructor can be defaulted since using smart pointers
    ~TradeArea() = default;
};

#endif // TRADE_AREA_H