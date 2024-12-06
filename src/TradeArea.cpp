#include "TradeArea.h"
#include "CardFactory.h"
#include "Card.h"
#include <string>

std::ostream& operator<<(std::ostream& out, const TradeArea& ta) {
    out << ta.cards.size();
    for (auto c : ta.cards) out << " " << c->getName();
    out << "\n";
    return out;
}

TradeArea::TradeArea(std::istream& in, CardFactory* factory) {
    int count; in >> count;
    for (int i=0; i<count; i++) {
        std::string name; in >> name;
        cards.push_back(factory->createCard(name));
    }
}
