#include "DiscardPile.h"
#include "CardFactory.h"
#include <stdexcept>

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

DiscardPile &DiscardPile::operator+=(std::unique_ptr<Card> card)
{
    if (!card)
    {
        throw std::invalid_argument("Cannot add null card to discard pile");
    }
    cards.push_back(std::move(card));
    return *this;
}

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

const Card *DiscardPile::top() const
{
    if (cards.empty())
    {
        throw std::runtime_error("Cannot get top card from empty discard pile");
    }
    return cards.back().get();
}

bool DiscardPile::empty() const
{
    return cards.empty();
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