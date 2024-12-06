#include "Table.h"

// Constructor initializes the players and sets up the game elements
Table::Table(Player& p1, Player& p2) 
    : player1(p1), player2(p2), deck(CardFactory::getFactory()->getDeck()), discardPile(), tradeArea() {}

// Checks if a player has won
bool Table::win(const Player& player) const {
    // Assuming the player needs a certain number of coins to win (e.g., 30 coins)
    return player.getNumCoins() >= 30;
}

// Prints the table state
void Table::print(std::ostream& out) const {
    out << "Current Table State:" << "\n";
    out << "Player 1: " << player1 << "\n";
    out << "Player 2: " << player2 << "\n";
    out << "Trade Area: " << tradeArea << "\n";
    out << "Discard Pile: ";
    discardPile.print(out);
    out << "\n";
    out << "========================" << std::endl; // Add separator for readability
}

// Add a card to the trade area
void Table::addCardToTradeArea(Card* card) {
    tradeArea += card;
}

// Getters for various game elements
DiscardPile& Table::getDiscardPile() {
    return discardPile;
}

TradeArea& Table::getTradeArea() {
    return tradeArea;
}

Deck& Table::getDeck() {
    return deck;
}

// Stream insertion operator for saving the game state
std::ostream& operator<<(std::ostream& out, const Table& table) {
    out << table.player1 << std::endl;
    out << table.player2 << std::endl;
    out << table.deck << std::endl;
    out << table.discardPile << std::endl;
    out << table.tradeArea << std::endl;
    return out;
}

// Stream extraction operator for loading the game state
std::istream& operator>>(std::istream& in, Table& table) {
    in >> table.player1;
    in >> table.player2;
    in >> table.deck;
    in >> table.discardPile;
    in >> table.tradeArea;
    return in;
}
