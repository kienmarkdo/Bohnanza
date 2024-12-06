#include "TradeArea.h"
#include "CardFactory.h"
#include <algorithm>
#include <stdexcept>

/**
 * @brief Constructs a TradeArea from a saved game state
 *
 * @param in Input stream containing serialized trade area data
 * @param factory Pointer to the CardFactory used to create cards
 *
 * Reads card names from the input stream until "END_TRADE" is encountered.
 * Each card is recreated using the provided CardFactory.
 */
TradeArea::TradeArea(std::istream &in, const CardFactory *factory)
{
    cards.clear();
    std::string cardName;

    while (std::getline(in, cardName))
    {
        if (cardName == "END_TRADE")
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
            std::cerr << "Error loading trade area card: " << e.what() << std::endl;
        }
    }
}

/**
 * @brief Adds a card to the trade area
 *
 * @param card Unique pointer to the card being added
 * @return Reference to the modified TradeArea
 * @throws std::invalid_argument if card pointer is null
 */
TradeArea &TradeArea::operator+=(std::unique_ptr<Card> card)
{
    if (!card)
    {
        throw std::invalid_argument("Cannot add null card to trade area");
    }
    cards.push_back(std::move(card));
    return *this;
}

/**
 * @brief Checks if a card can legally be added to the trade area
 *
 * @param card Pointer to the card to check
 * @return true if the card can be added, false otherwise
 *
 * A card can be added if either:
 * - The trade area is empty
 * - There is already a card of the same type in the trade area
 */
bool TradeArea::legal(const Card *card) const
{
    if (!card)
    {
        return false;
    }

    if (cards.empty())
    {
        return true;
    }

    // Check if there's already a card of the same type
    return std::any_of(cards.begin(), cards.end(),
                       [cardName = card->getName()](const auto &existing)
                       {
                           return existing->getName() == cardName;
                       });
}

/**
 * @brief Removes and returns a specific bean card from the trade area
 *
 * @param bean Name of the bean card to trade
 * @return Unique pointer to the traded card
 * @throws std::runtime_error if no matching bean card is found
 */
std::unique_ptr<Card> TradeArea::trade(const std::string &bean)
{
    auto it = std::find_if(cards.begin(), cards.end(),
                           [&bean](const auto &card)
                           { return card->getName() == bean; });

    if (it == cards.end())
    {
        throw std::runtime_error("No matching bean card found in trade area");
    }

    auto tradedCard = std::move(*it);
    cards.erase(it);
    return tradedCard;
}

/**
 * @brief Checks if a specific bean card exists in the trade area
 *
 * @param beanName Name of the bean card to check for
 * @return true if the bean exists in the trade area, false otherwise
 */
bool TradeArea::contains(const std::string &beanName) const
{
    return std::any_of(cards.begin(), cards.end(),
                       [&beanName](const auto &card)
                       {
                           return card->getName() == beanName;
                       });
}

/**
 * @brief Serializes the trade area to an output stream
 *
 * @param out Output stream to write to
 *
 * Writes:
 * - Number of cards
 * - Each card's name
 * - "END_TRADE" marker
 */
void TradeArea::serialize(std::ostream &out) const
{
    out << cards.size() << "\n";
    for (const auto &card : cards)
    {
        out << card->getName() << "\n";
    }
    out << "END_TRADE\n";
}

/**
 * @brief Stream insertion operator for TradeArea
 *
 * @param out Output stream
 * @param tradeArea TradeArea to output
 * @return Reference to the output stream
 *
 * Prints "(empty)" if trade area is empty,
 * otherwise prints names of all cards with spaces between them.
 */
std::ostream &operator<<(std::ostream &out, const TradeArea &tradeArea)
{
    if (tradeArea.empty())
    {
        out << "(empty)";
    }
    else
    {
        for (const auto &card : tradeArea.cards)
        {
            out << card->getName();
            out << " ";
        }
    }
    return out;
}