#ifndef DECK_H
#define DECK_H

#include <vector>
#include <memory>
#include <iostream>
#include "Card.h"

class CardFactory;

/**
 * @brief The Deck class represents a deck of bean cards. It allows drawing from the top,
 *        adding cards, checking if empty, and serialization.
 */
class Deck {
private:
    std::vector<std::unique_ptr<Card>> cards;

public:
    Deck() = default;

    /**
     * @brief Construct a Deck from an input stream, loading previously saved cards.
     * @param in Input stream containing saved deck data.
     * @param factory CardFactory used to recreate cards by name.
     */
    Deck(std::istream &in, const CardFactory *factory);

    Deck(Deck &&) noexcept = default;
    Deck &operator=(Deck &&) noexcept = default;

    Deck(const Deck &) = delete;
    Deck &operator=(const Deck &) = delete;

    /**
     * @brief Draw the top card from the deck.
     * @return A unique_ptr to the drawn Card.
     * @throws std::runtime_error if the deck is empty.
     */
    std::unique_ptr<Card> draw();

    /**
     * @brief Add a card to the deck (to the top).
     * @param card The card to add.
     * @throws std::invalid_argument if card is null.
     */
    void addCard(std::unique_ptr<Card> card);

    bool empty() const { return cards.empty(); }
    size_t size() const { return cards.size(); }

    /**
     * @brief Serialize the deck to an output stream (saving the order of cards).
     * @param out The output stream.
     */
    void serialize(std::ostream &out) const;

    friend std::ostream &operator<<(std::ostream &out, const Deck &deck);

    ~Deck() = default;
};

#endif // DECK_H
