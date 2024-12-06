#include "Deck.h"
#include "CardFactory.h"
#include <sstream>

// Constructor to initialize deck with given cards
Deck::Deck(std::vector<std::unique_ptr<Card>>&& cards) {
    for (auto& card : cards) {
        this->cards.push_back(card.release()); // Convert unique_ptr to raw pointer
    }
}

// Draws a card from the top of the deck
Card* Deck::draw() {
    if (cards.empty()) return nullptr;
    Card* topCard = cards.back();
    cards.pop_back();
    return topCard;
}

// Get the number of cards remaining in the deck
int Deck::size() const {
    return static_cast<int>(cards.size());
}

// Stream insertion operator to print the entire deck to an output stream
std::ostream& operator<<(std::ostream& out, const Deck& deck) {
    for (Card* card : deck.cards) {
        card->print(out);
        out << " ";
    }
    return out;
}

std::istream& operator>>(std::istream& in, Deck& deck) {
    std::string cardName;
    while (in >> cardName) {
        Card* card = CardFactory::getFactory()->getCard(cardName);
        if (card) {
            deck.cards.push_back(card);
        }
    }
    return in;
}
