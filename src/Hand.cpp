#include "Hand.h"
#include "CardFactory.h"
#include "Card.h"
#include <string>

std::ostream& operator<<(std::ostream& out, const Hand& h) {
    out << h.cards.size();
    for (auto c : h.cards) out << " " << c->getName();
    return out;
}

Hand::Hand(std::istream& in, CardFactory* factory) {
    int count; in >> count;
    for (int i=0; i<count; i++) {
        std::string name; in >> name;
        cards.push_back(factory->createCard(name));
    }
}
