#ifndef CARDFACTORY_H
#define CARDFACTORY_H

#include <vector>
#include <random>
#include "Card.h"
#include "Deck.h"

class CardFactory {
private:
    std::vector<Card*> cards; 
    static CardFactory* factoryInstance;

    // Private constructor: builds all cards in standard distribution
    CardFactory();

public:
    // No copying allowed for singleton
    CardFactory(const CardFactory&) = delete;
    CardFactory& operator=(const CardFactory&) = delete;

    // Get the singleton instance
    static CardFactory* getFactory();

    // Returns a Deck containing all cards in a random order
    Deck getDeck();

    ~CardFactory();
};

#endif
