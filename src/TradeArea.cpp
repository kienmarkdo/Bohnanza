#include "TradeArea.h"

TradeArea& TradeArea::operator+=(Card* card) {
    cards.push_back(card);
    return *this;
}

bool TradeArea::legal(Card* card) const {
    if (cards.empty()) {
        // If the trade area is empty, allow the first card of any bean.
        return true;
    }

    std::string name = card->getName();
    for (auto c : cards) {
        if (c->getName() == name) {
            return true;
        }
    }
    return false;
}

Card* TradeArea::trade(const std::string& beanName) {
    for (auto it = cards.begin(); it != cards.end(); ++it) {
        if ((*it)->getName() == beanName) {
            Card* c = *it;
            cards.erase(it);
            return c;
        }
    }
    return nullptr;
}

std::ostream& operator<<(std::ostream& out, const TradeArea& ta) {
    for (auto c : ta.cards) {
        out << *c << " ";
    }
    return out;
}
