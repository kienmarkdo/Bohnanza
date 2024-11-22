#include "Hand.h"

// Constructor: Reconstructs the Hand from a file
Hand::Hand(std::istream &in, const CardFactory *factory)
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

// Adds a card to the rear of the hand
Hand &Hand::operator+=(Card *card)
{
    cards.push_back(card);
    return *this;
}

// Returns and removes the top card from the player's hand
Card *Hand::play()
{
    if (cards.empty())
    {
        return nullptr; // Return nullptr if the hand is empty
    }
    Card *topCard = cards.front();
    cards.pop_front();
    return topCard;
}

// Returns but does not remove the top card from the player's hand
Card *Hand::top() const
{
    if (cards.empty())
    {
        return nullptr; // Return nullptr if the hand is empty
    }
    return cards.front();
}

// Returns and removes the card at the given index
Card *Hand::operator[](int index)
{
    if (index < 0 || index >= static_cast<int>(cards.size()))
    {
        throw std::out_of_range("Invalid card index");
    }
    auto it = cards.begin() + index;
    Card *selectedCard = *it;
    cards.erase(it); // Remove the card from the hand
    return selectedCard;
}

// Prints all the cards in the hand
std::ostream &operator<<(std::ostream &out, const Hand &hand)
{
    for (const auto &card : hand.cards)
    {
        card->print(out);
        out << " ";
    }
    return out;
}