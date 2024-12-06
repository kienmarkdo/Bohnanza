#ifndef HAND_H
#define HAND_H

#include <list>
#include <memory>
#include <iostream>
#include "Card.h"

class CardFactory;

class Hand
{
public:
    /**
     * @brief Default constructor creates an empty hand
     */
    Hand() = default;

    /**
     * @brief Constructs a Hand from saved game data
     * @param in Input stream containing serialized hand data
     * @param factory Pointer to the CardFactory for creating cards
     */
    Hand(std::istream &in, const CardFactory *factory);

    /**
     * @brief Move constructor
     */
    Hand(Hand &&) noexcept = default;

    /**
     * @brief Move assignment operator
     */
    Hand &operator=(Hand &&) noexcept = default;

    /**
     * @brief Copy constructor (deleted)
     * @details Copying is disabled because the class manages unique resources
     */
    Hand(const Hand &) = delete;

    /**
     * @brief Copy assignment operator (deleted)
     * @details Copying is disabled because the class manages unique resources
     */
    Hand &operator=(const Hand &) = delete;

    /**
     * @brief Adds a card to the hand
     * @param card Unique pointer to the card to add
     * @return Reference to the modified Hand
     */
    Hand &operator+=(std::unique_ptr<Card> card);

    /**
     * @brief Plays and removes the first card from the hand
     * @return Unique pointer to the played card
     * @throws std::runtime_error if hand is empty
     */
    std::unique_ptr<Card> play();

    /**
     * @brief Returns a pointer to the first card without removing it
     * @return Raw pointer to the first card
     * @throws std::runtime_error if hand is empty
     */
    const Card *top() const;

    /**
     * @brief Removes and returns the card at the specified index
     * @param index Position of the card to remove (0-based)
     * @return Unique pointer to the removed card
     * @throws std::out_of_range if index is invalid
     */
    std::unique_ptr<Card> operator[](int index);

    /**
     * @brief Adds a card to the front of the hand
     * @param card Unique pointer to the card to add
     */
    void addToFront(std::unique_ptr<Card> card);

    /**
     * @brief Checks if the hand is empty
     * @return true if hand contains no cards, false otherwise
     */
    bool empty() const { return cards.empty(); }

    /**
     * @brief Gets the number of cards in the hand
     * @return Current number of cards
     */
    size_t size() const { return cards.size(); }

    /**
     * @brief Serializes the hand to an output stream
     * @param out Output stream to write to
     */
    void serialize(std::ostream &out) const;

    /**
     * @brief Stream insertion operator for Hand
     * @param out Output stream
     * @param hand Hand to output
     * @return Reference to the output stream
     */
    friend std::ostream &operator<<(std::ostream &out, const Hand &hand);

    /**
     * @brief Gets a const reference to the cards in the hand
     * @return Const reference to the list of cards
     */
    const std::list<std::unique_ptr<Card>> &getCards() const { return cards; }

    /**
     * @brief Default destructor
     * @details Can be defaulted since using smart pointers
     */
    ~Hand() = default;

private:
    /** @brief List storing the cards in the hand */
    std::list<std::unique_ptr<Card>> cards;

    /**
     * @brief Validates if an index is within bounds
     * @param index Index to validate
     * @throws std::out_of_range if index is invalid
     */
    void validateIndex(int index) const;
};

#endif // HAND_H