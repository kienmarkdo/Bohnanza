#include "CardFactory.h"
#include <algorithm>   // for std::shuffle
#include <chrono>
#include <stdexcept>

// Static member definition
CardFactory* CardFactory::factoryInstance = nullptr;

CardFactory::CardFactory() {
    // Build all cards according to distribution
    // Blue (20)
    for (int i = 0; i < 20; ++i) {
        cards.push_back(new Blue());
    }
    // Chili (18)
    for (int i = 0; i < 18; ++i) {
        cards.push_back(new Chili());
    }
    // Stink (16)
    for (int i = 0; i < 16; ++i) {
        cards.push_back(new Stink());
    }
    // Green (14)
    for (int i = 0; i < 14; ++i) {
        cards.push_back(new Green());
    }
    // Soy (12)
    for (int i = 0; i < 12; ++i) {
        cards.push_back(new Soy());
    }
    // Black (10)
    for (int i = 0; i < 10; ++i) {
        cards.push_back(new Black());
    }
    // Red (8)
    for (int i = 0; i < 8; ++i) {
        cards.push_back(new Red());
    }
    // Garden (6)
    for (int i = 0; i < 6; ++i) {
        cards.push_back(new Garden());
    }
}

CardFactory* CardFactory::getFactory() {
    if (factoryInstance == nullptr) {
        factoryInstance = new CardFactory();
    }
    return factoryInstance;
}

Deck CardFactory::getDeck() {
    // Create a copy of all cards
    std::vector<Card*> deckCards = cards;

    // Shuffle
    unsigned seed = (unsigned)std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(deckCards.begin(), deckCards.end(), std::default_random_engine(seed));

    // Create a Deck object and return
    return Deck(deckCards);
}

CardFactory::~CardFactory() {
    // Destroy all cards
    for (auto c : cards) {
        delete c;
    }
    cards.clear();
}
