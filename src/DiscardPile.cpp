#include "DiscardPile.h"
#include "CardFactory.h"
#include <stdexcept>

/**
 * @brief Constructs a DiscardPile from a saved game state
 *
 * @param in Input stream containing serialized discard pile data
 * @param factory Pointer to the CardFactory used to create cards
 *
 * Reads card names from the input stream until "END_DISCARD" is encountered.
 * Each card is recreated using the provided CardFactory.
 */
DiscardPile::DiscardPile(std::istream &in, const CardFactory *factory)
{
    cards.clear();
    std::string cardName;

    while (std::getline(in, cardName))
    {
        if (cardName == "END_DISCARD")
        {
            break;
        }

        try
        {
            // Create card from saved name using factory
            auto card = std::unique_ptr<Card>(factory->getFactory()->createCard(cardName));
            if (card)
            {
                cards.push_back(std::move(card));
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error loading discarded card: " << e.what() << std::endl;
        }
    }
}

/**
 * @brief Adds a card to the top of the discard pile
 *
 * @param card Unique pointer to the card being discarded
 * @return Reference to the modified DiscardPile
 * @throws std::invalid_argument if card pointer is null
 */
DiscardPile &DiscardPile::operator+=(std::unique_ptr<Card> card)
{
    if (!card)
    {
        throw std::invalid_argument("Cannot add null card to discard pile");
    }
    cards.push_back(std::move(card));
    return *this;
}

/**
 * @brief Removes and returns the top card from the discard pile
 *
 * @return Unique pointer to the picked up card
 * @throws std::runtime_error if the discard pile is empty
 */
std::unique_ptr<Card> DiscardPile::pickUp()
{
    if (cards.empty())
    {
        throw std::runtime_error("Cannot pick up from empty discard pile");
    }

    std::unique_ptr<Card> topCard = std::move(cards.back());
    cards.pop_back();
    return topCard;
}

/**
 * @brief Returns a pointer to the top card without removing it
 *
 * @return Raw pointer to the top card
 * @throws std::runtime_error if the discard pile is empty
 */
const Card *DiscardPile::top() const
{
    if (cards.empty())
    {
        throw std::runtime_error("Cannot get top card from empty discard pile");
    }
    return cards.back().get();
}

/**
 * @brief Checks if the discard pile is empty
 *
 * @return true if pile contains no cards, false otherwise
 */
bool DiscardPile::empty() const
{
    return cards.empty();
}

/**
 * @brief Prints the current state of the discard pile
 *
 * @param out Output stream to print to
 *
 * Prints "(empty)" if pile is empty, otherwise prints the name
 * of the top card.
 */
void DiscardPile::print(std::ostream &out) const
{
    out << "Discard Pile: ";
    if (empty())
    {
        out << "(empty)";
    }
    else if (const Card *topCard = top())
    {
        out << topCard->getName();
    }
    out << "\n";
}

/**
 * @brief Serializes the discard pile to an output stream
 *
 * @param out Output stream to write to
 *
 * Writes each card's name followed by a newline.
 * Ends with "END_DISCARD" marker.
 */
void DiscardPile::serialize(std::ostream &out) const
{
    for (const auto &card : cards)
    {
        if (card)
        {
            out << card->getName() << "\n";
        }
    }
    out << "END_DISCARD\n";
}

/**
 * @brief Stream insertion operator for DiscardPile
 *
 * @param out Output stream
 * @param pile DiscardPile to output
 * @return Reference to the output stream
 *
 * Prints "(empty)" if pile is empty, otherwise prints the name
 * of the top card.
 */
std::ostream &operator<<(std::ostream &out, const DiscardPile &pile)
{
    if (pile.empty())
    {
        out << "(empty)";
    }
    else
    {
        try
        {
            const Card *topCard = pile.top();
            if (topCard)
            {
                out << topCard->getName();
            }
        }
        catch (const std::runtime_error &)
        {
            out << "(empty)";
        }
    }
    return out;
}