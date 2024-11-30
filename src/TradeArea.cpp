#include "TradeArea.h"
#include "CardFactory.h"
#include <algorithm>
#include <stdexcept>

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

TradeArea &TradeArea::operator+=(std::unique_ptr<Card> card)
{
    if (!card)
    {
        throw std::invalid_argument("Cannot add null card to trade area");
    }
    cards.push_back(std::move(card));
    return *this;
}

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

    return std::any_of(cards.begin(), cards.end(),
                       [cardName = card->getName()](const auto &existing)
                       {
                           return existing->getName() == cardName;
                       });
}

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

bool TradeArea::contains(const std::string &beanName) const
{
    return std::any_of(cards.begin(), cards.end(),
                       [&beanName](const auto &card)
                       {
                           return card->getName() == beanName;
                       });
}

void TradeArea::serialize(std::ostream &out) const
{
    out << cards.size() << "\n";
    for (const auto &card : cards)
    {
        out << card->getName() << "\n";
    }
    out << "END_TRADE\n";
}

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
