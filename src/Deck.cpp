#include "Deck.h"

// Constructor: Initialize the Deck with all cards
Deck::Deck(const std::vector<Card *> &cards)
{
    this->assign(cards.begin(), cards.end()); // Copy cards into the Deck
    shuffle();                                // Shuffle the deck after initialization
}

// Constructor: Reconstruct the Deck from a file
Deck::Deck(std::istream &in, const CardFactory *factory)
{
    std::string cardName;
    while (in >> cardName)
    {
        Card *card = factory->getCard(cardName);
        if (card)
        {
            this->push_back(card);
        }
    }
    shuffle(); // Shuffle the deck after reconstruction
}

// Shuffles the Deck
void Deck::shuffle()
{
    // Use a random number generator
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(this->begin(), this->end(), g);
}

// Draws the top card from the Deck
Card *Deck::draw()
{
    if (this->empty())
    {
        return nullptr; // Return nullptr if the Deck is empty
    }
    Card *topCard = this->back();
    this->pop_back();
    return topCard;
}

// Prints all cards in the Deck
std::ostream &operator<<(std::ostream &out, const Deck &deck)
{
    for (const auto &card : deck)
    {
        card->print(out);
        out << " ";
    }
    return out;
}