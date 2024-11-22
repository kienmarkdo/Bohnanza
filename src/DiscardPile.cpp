#include "DiscardPile.h"

// Constructor: Reconstruct the DiscardPile from a file
DiscardPile::DiscardPile(std::istream &in, const CardFactory *factory)
{
    std::string cardName;
    while (in >> cardName)
    { // Read card names from the input stream
        Card *card = factory->getCard(cardName);
        if (card)
        {
            pile.push_back(card);
        }
    }
}

// Discard a card to the pile
DiscardPile &DiscardPile::operator+=(Card *card)
{
    pile.push_back(card);
    return *this;
}

// Remove and return the top card from the pile
Card *DiscardPile::pickUp()
{
    if (pile.empty())
    {
        return nullptr; // Return nullptr if the pile is empty
    }
    Card *topCard = pile.back();
    pile.pop_back();
    return topCard;
}

// Return but do not remove the top card
Card *DiscardPile::top() const
{
    if (pile.empty())
    {
        return nullptr; // Return nullptr if the pile is empty
    }
    return pile.back();
}

// Print all cards in the DiscardPile
void DiscardPile::print(std::ostream &out) const
{
    for (const auto &card : pile)
    {
        card->print(out);
        out << " ";
    }
}

// Stream insertion operator to insert only the top card
std::ostream &operator<<(std::ostream &out, const DiscardPile &discardPile)
{
    if (!discardPile.pile.empty())
    {
        discardPile.pile.back()->print(out); // Print only the top card
    }
    else
    {
        out << "Empty"; // Indicate the pile is empty
    }
    return out;
}