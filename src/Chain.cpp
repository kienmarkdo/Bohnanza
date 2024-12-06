#include "Chain.h"
#include "CardFactory.h"

template<>
Chain<Card*>::Chain(Card* card) {
    // Add the initial card to the chain
    cards.push_back(card);
}

template<>
Chain<Card*>& Chain<Card*>::operator+=(Card* card) {
    // Add the card to the chain
    cards.push_back(card);
    return *this;
}

template <class T>
Chain<T>& Chain<T>::operator+=(Card* card) {
    if (dynamic_cast<T*>(card) == nullptr) {
        throw IllegalType(); // Card type doesn't match the chain's type
    }
    cards.push_back(card);
    return *this;
}

std::istream& operator>>(std::istream& in, Chain<Card*>& chain) {
    // Deserialize the cards in the chain
    std::string cardName;
    chain.cards.clear();  // Clear existing cards in the chain
    int numCards;
    in >> numCards;       // Read the number of cards in the chain

    for (int i = 0; i < numCards; ++i) {
        in >> cardName;
        Card* card = CardFactory::getFactory()->getCard(cardName);
        if (card) {
            chain.cards.push_back(card);
        }
    }

    return in;
}
