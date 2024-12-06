#include "Table.h"
#include "CardFactory.h"

Table::Table(const std::string& p1Name, const std::string& p2Name, Deck&& initialDeck)
    : player1(p1Name), player2(p2Name), deck(std::move(initialDeck))
{
}

Table::Table(std::istream& in, CardFactory* factory)
    : player1(in, factory), player2(in, factory), deck(in, factory), discardPile(in, factory), tradeArea(in, factory)
{
}

std::ostream& operator<<(std::ostream& out, const Table& table) {
    out << table.player1 << "\n" << table.player2 << "\n" << table.deck << table.discardPile << table.tradeArea;
    return out;
}
