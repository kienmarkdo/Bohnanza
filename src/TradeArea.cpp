#include "TradeArea.h"
#include <algorithm>
#include "CardFactory.h"
#include <stdexcept>

TradeArea::TradeArea(std::istream &in, const CardFactory *factory)
{
    cards.clear(); // Clear existing cards
    std::string cardName;

    while (std::getline(in, cardName))
    {
        if (cardName == "END_TRADE")
        {
            break;
        }

        try
        {
            Card *card = factory->getFactory()->createCard(cardName);
            if (card)
            {
                cards.push_back(card);
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error loading trade area card: " << e.what() << std::endl;
        }
    }
}

TradeArea &TradeArea::operator+=(Card *card)
{
    if (card == nullptr)
    {
        throw std::invalid_argument("Cannot add null card to trade area");
    }
    cards.push_back(card);
    return *this;
}

bool TradeArea::legal(Card *card) const
{
    if (card == nullptr)
    {
        return false;
    }

    // Empty trade area always accepts cards
    if (cards.empty())
    {
        return true;
    }

    // Check if there's already a card of the same type
    return std::any_of(cards.begin(), cards.end(),
                       [card](const Card *existing)
                       {
                           return existing->getName() == card->getName();
                       });
}

Card *TradeArea::trade(const std::string &bean)
{
    // Find the first card matching the bean name
    auto it = std::find_if(cards.begin(), cards.end(),
                           [&bean](const Card *card)
                           {
                               return card->getName() == bean;
                           });

    if (it == cards.end())
    {
        throw std::runtime_error("No matching bean card found in trade area");
    }

    // Remove and return the card
    Card *tradedCard = *it;
    cards.erase(it);
    return tradedCard;
}

bool TradeArea::contains(const std::string &beanName) const
{
    return std::any_of(cards.begin(), cards.end(),
                       [&beanName](const Card *card)
                       {
                           return card->getName() == beanName;
                       });
}

std::ostream &operator<<(std::ostream &out, const TradeArea &tradeArea)
{
    out << "Trade Area: ";
    for (const auto &card : tradeArea.cards)
    {
        card->print(out);
        out << " ";
    }
    return out;
}

TradeArea::~TradeArea()
{
    for (Card *card : cards)
    {
        delete card;
    }
    cards.clear();
}

TradeArea::TradeArea(TradeArea &&other) noexcept
    : cards(std::move(other.cards))
{
    other.cards.clear();
}

TradeArea &TradeArea::operator=(TradeArea &&other) noexcept
{
    if (this != &other)
    {
        // Clean up existing cards
        for (Card *card : cards)
        {
            delete card;
        }
        cards = std::move(other.cards);
        other.cards.clear();
    }
    return *this;
}

void TradeArea::serialize(std::ostream &out) const
{
    // Store the number of cards first
    out << cards.size() << "\n";

    // Store each card's type
    for (const Card *card : cards)
    {
        out << card->getName() << "\n";
    }
}