#ifndef CARDFACTORY_H
#define CARDFACTORY_H

#include <vector>
#include <algorithm>
#include <random>
#include <memory>
#include "Card.h"

// Singleton class for managing card creation and providing a shuffled deck
class CardFactory {
public:
    static CardFactory* getFactory();
    std::vector<std::unique_ptr<Card>> getDeck();
    Card* getCard(const std::string& cardName) const;
    ~CardFactory();

private:
    CardFactory();
    void initializeDeck();
    static std::unique_ptr<CardFactory> instance; // Use unique_ptr for automatic cleanup
    std::vector<std::unique_ptr<Card>> deck;
};

#endif // CARDFACTORY_H
