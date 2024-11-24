#include "DiscardPile.h"
#include "CardFactory.h"
#include <stdexcept>
#include "Card.h"

DiscardPile::DiscardPile(std::istream &in, const CardFactory *factory)
{
    cards.clear(); // Clear existing cards
    std::string cardName;

    while (std::getline(in, cardName))
    {
        if (cardName == "END_DISCARD")
        {
            break;
        }

        try
        {
            // Note: Remove getFactory() call since factory is already passed in
            Card *card = factory->getFactory()->createCard(cardName);
            if (card)
            {
                cards.push_back(card);
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error loading discarded card: " << e.what() << std::endl;
        }
    }
}
DiscardPile &DiscardPile::operator+=(Card *card)
{
    if (card == nullptr)
    {
        throw std::invalid_argument("Cannot add null card to discard pile");
    }
    cards.push_back(card);
    return *this;
}

Card *DiscardPile::pickUp()
{
    if (cards.empty())
    {
        throw std::runtime_error("Cannot pick up from empty discard pile");
    }

    Card *topCard = cards.back();
    cards.pop_back();
    return topCard;
}

Card *DiscardPile::top() const
{
    if (cards.empty())
    {
        throw std::runtime_error("Cannot get top card from empty discard pile");
    }

    return cards.back();
}

void DiscardPile::print(std::ostream &out) const
{
    out << "Discard Pile: ";
    for (const auto &card : cards)
    {
        card->print(out);
        out << " ";
    }
    out << "\n";
}

std::ostream &operator<<(std::ostream &out, const DiscardPile &pile)
{
    if (pile.empty())
    {
        out << "(empty)";
    }
    else if (pile.top())
    {
        pile.top()->print(out);
    }
    return out;
}

DiscardPile::~DiscardPile()
{
    for (Card *card : cards)
    {
        delete card;
    }
    cards.clear();
}

DiscardPile::DiscardPile(DiscardPile &&other) noexcept
    : cards(std::move(other.cards))
{
    other.cards.clear();
}

DiscardPile &DiscardPile::operator=(DiscardPile &&other) noexcept
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

// Serialize method - saves to file
void DiscardPile::serialize(std::ostream &out) const
{
    for (const Card *card : cards)
    {
        if (card)
        {
            out << card->getName() << "\n";
        }
    }
    out << "END_DISCARD\n";
}
