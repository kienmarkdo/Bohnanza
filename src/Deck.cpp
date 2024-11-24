#include "Deck.h"
#include <algorithm>
#include <stdexcept>
#include "CardFactory.h"

Deck::Deck(std::istream &in, const CardFactory *factory)
{
    this->clear();
    std::string cardName;

    while (std::getline(in, cardName))
    {
        if (cardName == "END_DECK")
        {
            break;
        }

        try
        {
            Card *card = factory->getFactory()->createCard(cardName);
            if (card)
            {
                this->push_back(card);
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error loading deck card: " << e.what() << std::endl;
        }
    }
}

Card *Deck::draw()
{
    if (this->empty())
    {
        throw std::runtime_error("Cannot draw from empty deck");
    }

    // Get the top card
    Card *card = this->back();

    // Remove it from the deck
    this->pop_back();

    return card;
}

std::ostream &operator<<(std::ostream &out, const Deck &deck)
{
    // Print all cards in the deck
    for (const auto &card : deck)
    {
        card->print(out);
        out << " ";
    }
    return out;
}

Deck::~Deck()
{

    this->clear();
}

Deck::Deck(Deck &&other) noexcept
    : std::vector<Card *>(std::move(other))
{
    // The vector move constructor will handle the pointer transfer
}

Deck &Deck::operator=(Deck &&other) noexcept
{
    if (this != &other)
    {
        // Clean up existing cards
        for (Card *card : *this)
        {
            delete card;
        }

        // Move the vector contents
        std::vector<Card *>::operator=(std::move(other));
    }
    return *this;
}

void Deck::serialize(std::ostream &out) const
{
    // Store the number of cards first
    for (const Card *card : *this)
    {
        if (card)
        {
            out << card->getName() << "\n";
        }
    }
    out << "END_DECK\n";
}

// bool Deck::empty() const
// {
//     if (this == nullptr)
//     {
//         return true; // Consider null deck as empty
//     }
//     return std::vector<Card *>::empty();
// }
