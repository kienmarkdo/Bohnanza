#include "Table.h"

bool Table::win() const {
    // Game over condition: if deck is empty. Or if some other condition is specified, adjust.
    return deck.size() == 0;
}

std::ostream& operator<<(std::ostream& out, const Table& table) {
    // Print players
    out << "Player 1: " << table.player1 << std::endl;
    out << "Player 2: " << table.player2 << std::endl;

    // Print discard pile
    out << "Discard Pile: " << table.discardPile << std::endl;

    // Print trade area
    out << "Trade Area: " << table.tradeArea << std::endl;

    // Print deck size
    out << "Deck size: " << table.deck.size() << " cards remaining." << std::endl;
    return out;
}
