#include "TradeArea.h"

// Constructor: Reconstruct the TradeArea from a file
TradeArea::TradeArea(std::istream &in, const CardFactory *factory)
{
    std::string cardName;
    while (in >> cardName)
    { // Read card names from the input stream
        Card *card = factory->getCard(cardName);
        if (card)
        {
            cards.push_back(card);
        }
    }
}

// Adds a card to the TradeArea
TradeArea &TradeArea::operator+=(Card *card)
{
    cards.push_back(card);
    return *this;
}

// Checks if the card can be legally added to the TradeArea
bool TradeArea::legal(Card *card) const
{
    for (const auto &c : cards)
    {
        if (c->getName() == card->getName())
        {
            return true;
        }
    }
    return false;
}

// Removes and returns a card of the specified bean name
Card *TradeArea::trade(const std::string &beanName)
{
    for (auto it = cards.begin(); it != cards.end(); ++it)
    {
        if ((*it)->getName() == beanName)
        {
            Card *card = *it;
            cards.erase(it);
            return card;
        }
    }
    return nullptr; // Return nullptr if no matching card is found
}

// Returns the number of cards in the TradeArea
int TradeArea::numCards() const
{
    return cards.size();
}

// Stream insertion operator to print all cards in the TradeArea
std::ostream &operator<<(std::ostream &out, const TradeArea &tradeArea)
{
    for (const auto &card : tradeArea.cards)
    {
        card->print(out);
        out << " ";
    }
    return out;
}