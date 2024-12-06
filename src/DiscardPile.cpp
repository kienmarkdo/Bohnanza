#include "DiscardPile.h"

DiscardPile& DiscardPile::operator+=(Card* card) {
    pile.push_back(card);
    return *this;
}

Card* DiscardPile::pickUp() {
    if (pile.empty()) return nullptr;
    Card* topCard = pile.back();
    pile.pop_back();
    return topCard;
}

Card* DiscardPile::top() const {
    if (pile.empty()) return nullptr;
    return pile.back();
}

std::ostream& operator<<(std::ostream& out, const DiscardPile& dp) {
    // print top to bottom: top is at the back
    for (auto it = dp.pile.rbegin(); it != dp.pile.rend(); ++it) {
        out << **it << " ";
    }
    return out;
}
