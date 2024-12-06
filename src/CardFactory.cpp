#include "CardFactory.h"
#include <algorithm>
#include <random>
#include <chrono>

CardFactory* CardFactory::instance = nullptr;

CardFactory::CardFactory() {
    for (int i=0; i<20; i++) cards.push_back(new Blue());
    for (int i=0; i<18; i++) cards.push_back(new Chili());
    for (int i=0; i<16; i++) cards.push_back(new Stink());
    for (int i=0; i<14; i++) cards.push_back(new Green());
    for (int i=0; i<12; i++) cards.push_back(new Soy());
    for (int i=0; i<10; i++) cards.push_back(new Black());
    for (int i=0; i<8; i++) cards.push_back(new Red());
    for (int i=0; i<6; i++) cards.push_back(new Garden());
}

CardFactory* CardFactory::getFactory() {
    if (!instance) instance = new CardFactory();
    return instance;
}

Deck CardFactory::getDeck() {
    std::vector<Card*> deckCards = cards;
    unsigned seed = (unsigned)std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(deckCards.begin(), deckCards.end(), std::default_random_engine(seed));
    return Deck(deckCards);
}

Card* CardFactory::createCard(const std::string& name) {
    if (name=="Blue") return new Blue();
    if (name=="Chili") return new Chili();
    if (name=="Stink") return new Stink();
    if (name=="Green") return new Green();
    if (name=="Soy") return new Soy();
    if (name=="Black") return new Black();
    if (name=="Red") return new Red();
    if (name=="Garden") return new Garden();
    return nullptr;
}

CardFactory::~CardFactory() {
    for (auto c: cards) delete c;
    cards.clear();
}
