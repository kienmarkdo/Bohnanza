#include "TradeArea.h"
#include "CardFactory.h"

TradeArea::TradeArea() {
    // Nothing to initialize, as the trade area starts empty
}

// Add a card to the trade area
TradeArea& TradeArea::operator+=(Card* card) {
    tradeCards.push_back(card);
    return *this;
}

// Check if a card is legal to add to the trade area
bool TradeArea::legal(Card* card) const {

    // tradeCards list is empty
    if (tradeCards.empty()) {
        return false;
    }

    for (Card* c : tradeCards) {
        if (c->getName() == card->getName()) {
            return true;
        }
    }
    return false;
}

// Trade and remove a card from the trade area by name
Card* TradeArea::trade(const std::string& cardName) {
    for (auto it = tradeCards.begin(); it != tradeCards.end(); ++it) {
        if ((*it)->getName() == cardName) {
            Card* tradedCard = *it;
            tradeCards.erase(it);
            return tradedCard;
        }
    }
    return nullptr;
}

// Stream insertion operator to print the entire trade area
std::ostream& operator<<(std::ostream& out, const TradeArea& tradeArea) {
    for (Card* card : tradeArea.tradeCards) {
        card->print(out);
        out << " ";
    }
    return out;
}
