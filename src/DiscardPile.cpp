#include "DiscardPile.h"
#include "CardFactory.h"

DiscardPile::DiscardPile() {
    // Nothing to initialize, as pile starts empty
}

// Push a card onto the discard pile
void DiscardPile::push(Card* card) {
    pile.push_back(card);
}

// Pick up the top card from the discard pile
Card* DiscardPile::pickUp() {
    if (pile.empty()) return nullptr;
    Card* topCard = pile.back();
    pile.pop_back();
    return topCard;
}

// Peek at the top card of the discard pile without removing it
Card* DiscardPile::top() const {
    if (pile.empty()) return nullptr;
    return pile.back();
}

// Print all cards in the discard pile
void DiscardPile::print(std::ostream& out) const {
    for (Card* card : pile) {
        card->print(out);
        out << " ";
    }
}

// Stream insertion operator to print the discard pile
std::ostream& operator<<(std::ostream& out, const DiscardPile& discardPile) {
    discardPile.print(out);
    return out;
}

std::istream& operator>>(std::istream& in, DiscardPile& discardPile) {
    std::string cardName;
    while (in >> cardName) {
        Card* card = CardFactory::getFactory()->getCard(cardName);
        if (card) {
            discardPile.pile.push_back(card);
        }
    }
    return in;
}
