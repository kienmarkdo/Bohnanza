#include "Deck.h"
#include <algorithm>
#include <stdexcept>
#include "CardFactory.h"

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

void Deck::addCard(std::unique_ptr<Card> card)
{
    if (!card)
    {
        throw std::invalid_argument("Cannot add null card to deck");
    }
    cards.push_back(std::move(card));
}

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