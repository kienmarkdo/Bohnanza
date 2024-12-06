#ifndef CARDFACTORY_H
#define CARDFACTORY_H

#include <vector>
#include <string>
#include "Card.h"
#include "Deck.h"

class CardFactory {
private:
    std::vector<Card*> cards;
    static CardFactory* instance;
    CardFactory();
public:
    CardFactory(const CardFactory&) = delete;
    CardFactory& operator=(const CardFactory&) = delete;
    static CardFactory* getFactory();
    Deck getDeck();
    Card* createCard(const std::string& name);
    ~CardFactory();
};

#endif
