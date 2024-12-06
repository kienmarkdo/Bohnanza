#include "CardFactory.h"

CardFactory* CardFactory::instance = nullptr;

CardFactory::CardFactory() {
    initializeDeck();
}

CardFactory::~CardFactory() {}

CardFactory* CardFactory::getFactory() {
    if (instance == nullptr) {
        instance = new CardFactory();
    }
    return instance;
}

void CardFactory::initializeDeck() {
    // Add cards to the deck (based on game rules, each card type has a specific count)
    for (int i = 0; i < 20; ++i) deck.push_back(std::make_unique<Blue>());     // 20 Blue cards
    for (int i = 0; i < 18; ++i) deck.push_back(std::make_unique<Chili>());    // 18 Chili cards
    for (int i = 0; i < 16; ++i) deck.push_back(std::make_unique<Stink>());    // 16 Stink cards
    for (int i = 0; i < 14; ++i) deck.push_back(std::make_unique<Green>());    // 14 Green cards
    for (int i = 0; i < 12; ++i) deck.push_back(std::make_unique<Soy>());      // 12 Soy cards
    for (int i = 0; i < 10; ++i) deck.push_back(std::make_unique<Black>());    // 10 Black cards
    for (int i = 0; i < 8; ++i) deck.push_back(std::make_unique<Red>());       // 8 Red cards
    for (int i = 0; i < 6; ++i) deck.push_back(std::make_unique<Garden>());    // 6 Garden cards

    // Shuffle the deck
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(deck.begin(), deck.end(), g);
}

std::vector<std::unique_ptr<Card>> CardFactory::getDeck() {
    return std::move(deck);
}

Card* CardFactory::getCard(const std::string& cardName) const {
    if (cardName == "Blue") return new Blue();
    if (cardName == "Chili") return new Chili();
    if (cardName == "Stink") return new Stink();
    if (cardName == "Green") return new Green();
    if (cardName == "Soy") return new Soy();
    if (cardName == "Black") return new Black();
    if (cardName == "Red") return new Red();
    if (cardName == "Garden") return new Garden();
    return nullptr;
}