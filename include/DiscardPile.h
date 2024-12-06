#ifndef DISCARD_PILE_H
#define DISCARD_PILE_H

#include <vector>
#include <memory>
#include <iostream>
#include "Card.h"

class CardFactory;

/**
 * @class DiscardPile
 * @brief Manages the discard pile in the card game
 *
 * The DiscardPile class represents the pile where players discard their cards.
 * It provides functionality to add cards, pick up the top card, and view the current state.
 * The class uses RAII principles with smart pointers for memory management.
 */
class DiscardPile
{
private:
    /** @brief Vector storing the cards in the discard pile */
    std::vector<std::unique_ptr<Card>> cards;

public:
    /**
     * @brief Default constructor creates an empty discard pile
     */
    DiscardPile() = default;

    /**
     * @brief Constructs a DiscardPile from saved game data
     * @param in Input stream containing serialized discard pile data
     * @param factory Pointer to the CardFactory for creating cards
     */
    DiscardPile(std::istream &in, const CardFactory *factory);

    /**
     * @brief Move constructor
     */
    DiscardPile(DiscardPile &&other) noexcept = default;

    /**
     * @brief Move assignment operator
     */
    DiscardPile &operator=(DiscardPile &&other) noexcept = default;

    /**
     * @brief Copy constructor (deleted)
     * @details Copying is disabled because the class manages unique resources
     */
    DiscardPile(const DiscardPile &) = delete;

    /**
     * @brief Copy assignment operator (deleted)
     * @details Copying is disabled because the class manages unique resources
     */
    DiscardPile &operator=(const DiscardPile &) = delete;

    /**
     * @brief Adds a card to the discard pile
     * @param card Unique pointer to the card to add
     * @return Reference to the modified DiscardPile
     * @throws std::invalid_argument if card is null
     */
    DiscardPile &operator+=(std::unique_ptr<Card> card);

    /**
     * @brief Removes and returns the top card from the pile
     * @return Unique pointer to the picked up card
     * @throws std::runtime_error if pile is empty
     */
    std::unique_ptr<Card> pickUp();

    /**
     * @brief Returns a pointer to the top card without removing it
     * @return Raw pointer to the top card
     * @throws std::runtime_error if pile is empty
     */
    const Card *top() const;

    /**
     * @brief Checks if the discard pile is empty
     * @return true if pile contains no cards, false otherwise
     */
    bool empty() const;

    /**
     * @brief Prints the current state of the discard pile
     * @param out Output stream to print to
     */
    void print(std::ostream &out) const;

    /**
     * @brief Serializes the discard pile to an output stream
     * @param out Output stream to write to
     */
    void serialize(std::ostream &out) const;

    /**
     * @brief Default destructor
     * @details Can be defaulted since using smart pointers
     */
    ~DiscardPile() = default;

    /**
     * @brief Stream insertion operator for DiscardPile
     * @param out Output stream
     * @param pile DiscardPile to output
     * @return Reference to the output stream
     */
    friend std::ostream &operator<<(std::ostream &out, const DiscardPile &pile);
};

#endif // DISCARD_PILE_H