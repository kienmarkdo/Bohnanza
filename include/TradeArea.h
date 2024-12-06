#ifndef TRADE_AREA_H
#define TRADE_AREA_H

#include <vector>
#include <memory>
#include <iostream>
#include "Card.h"

class CardFactory;

/**
 * @brief Represents the trading area where cards can be exchanged
 * @details The TradeArea manages a collection of cards that are available
 *          for trading between players during the game.
 */
class TradeArea
{
private:
    std::vector<std::unique_ptr<Card>> cards; ///< Collection of cards in trade area

public:
    /** @brief Default constructor */
    TradeArea() = default;

    /**
     * @brief Constructs a trade area from saved state
     * @param in Input stream containing saved state
     * @param factory Pointer to card factory for card creation
     */
    TradeArea(std::istream &in, const CardFactory *factory);

    /** @brief Move constructor */
    TradeArea(TradeArea &&) noexcept = default;

    /** @brief Move assignment operator */
    TradeArea &operator=(TradeArea &&) noexcept = default;

    /** @brief Deleted copy constructor (non-copyable) */
    TradeArea(const TradeArea &) = delete;

    /** @brief Deleted copy assignment (non-copyable) */
    TradeArea &operator=(const TradeArea &) = delete;

    /**
     * @brief Adds a card to the trade area
     * @param card Unique pointer to the card to add
     * @return Reference to this trade area
     */
    TradeArea &operator+=(std::unique_ptr<Card> card);

    /**
     * @brief Checks if a card can be legally added
     * @param card Pointer to card to check
     * @return true if card can be added, false otherwise
     */
    bool legal(const Card *card) const;

    /**
     * @brief Attempts to trade a specific bean card
     * @param bean Name of the bean card to trade
     * @return Unique pointer to the traded card, nullptr if trade failed
     */
    std::unique_ptr<Card> trade(const std::string &bean);

    /**
     * @brief Checks if a specific bean exists in trade area
     * @param beanName Name of bean to check for
     * @return true if bean exists in trade area, false otherwise
     */
    bool contains(const std::string &beanName) const;

    /** @brief Checks if trade area is empty */
    bool empty() const { return cards.empty(); }

    /** @brief Gets number of cards in trade area */
    size_t numCards() const { return cards.size(); }

    /** @brief Iterator access for range-based for loops */
    auto begin() const { return cards.begin(); }
    auto end() const { return cards.end(); }

    /**
     * @brief Serializes trade area state to stream
     * @param out Output stream for serialization
     */
    void serialize(std::ostream &out) const;

    /**
     * @brief Outputs trade area state to stream
     * @param out Output stream
     * @param tradeArea Trade area to output
     * @return Reference to output stream
     */
    friend std::ostream &operator<<(std::ostream &out, const TradeArea &tradeArea);

    /** @brief Default destructor */
    ~TradeArea() = default;
};

#endif // TRADE_AREA_H