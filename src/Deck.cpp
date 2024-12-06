#include "Deck.h"
#include <algorithm>
#include <stdexcept>
#include "CardFactory.h"

/**
 * @brief Construct a Deck from saved data in a stream. Reads card names until "END_DECK".
 * @param in Input stream containing deck data.
 * @param factory CardFactory to recreate cards from names.
 */
Deck::Deck(std::istream &in, const CardFactory *factory)
{
    cards.clear();
    std::string cardName;

    while (std::getline(in, cardName))
    {
        if (cardName == "END_DECK")
        {
            break;
        }

        try
        {
            auto card = factory->getFactory()->createCard(cardName);
            if (card)
            {
                cards.push_back(std::move(card));
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error loading deck card: " << e.what() << std::endl;
        }
    }
}

/**
 * @brief Draw and remove the top card from the deck.
 * @return A unique_ptr to the drawn card.
 * @throws std::runtime_error if the deck is empty.
 */
std::unique_ptr<Card> Deck::draw()
{
    if (cards.empty())
    {
        throw std::runtime_error("Cannot draw from empty deck");
    }

    std::unique_ptr<Card> topCard = std::move(cards.back());
    cards.pop_back();
    return topCard;
}

/**
 * @brief Add a card to the top of the deck.
 * @param card The card to add. Must not be null.
 * @throws std::invalid_argument if card is null.
 */
void Deck::addCard(std::unique_ptr<Card> card)
{
    if (!card)
    {
        throw std::invalid_argument("Cannot add null card to deck");
    }
    cards.push_back(std::move(card));
}

/**
 * @brief Serialize the deck to an output stream, writing card names followed by "END_DECK".
 * @param out The output stream to write to.
 */
void Deck::serialize(std::ostream &out) const
{
    for (const auto &card : cards)
    {
        if (card)
        {
            out << card->getName() << "\n";
        }
    }
    out << "END_DECK\n";
}

/**
 * @brief Overload of operator<< for decks. Prints the deck's cards in order.
 * @param out Output stream.
 * @param deck The deck to print.
 * @return Reference to the output stream.
 */
std::ostream &operator<<(std::ostream &out, const Deck &deck)
{
    for (const auto &card : deck.cards)
    {
        if (card)
        {
            card->print(out);
            out << " ";
        }
    }
    return out;
}
