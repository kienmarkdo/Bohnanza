#include "Deck.h"
#include "CardFactory.h"
#include "Card.h"
#include <string>

std::ostream& operator<<(std::ostream& out, const Deck& d) {
    out << d.size();
    for (auto c : d.cards) out << " " << c->getName();
    out << "\n";
    return out;
}

Deck::Deck(std::istream& in, CardFactory* factory) {
    int count; in >> count;
    for (int i=0; i<count; i++) {
        std::string name; in >> name;
        cards.push_back(factory->createCard(name));
    }
}
