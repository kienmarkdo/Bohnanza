#include "DiscardPile.h"
#include "CardFactory.h"
#include "Card.h"
#include <string>

std::ostream& operator<<(std::ostream& out, const DiscardPile& dp) {
    out << dp.pile.size();
    for (auto c: dp.pile) out << " " << c->getName();
    out << "\n";
    return out;
}

DiscardPile::DiscardPile(std::istream& in, CardFactory* factory) {
    int count; in >> count;
    for (int i=0; i<count; i++) {
        std::string name; in >> name;
        pile.push_back(factory->createCard(name));
    }
}
