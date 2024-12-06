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
    out << "Player 1: " << player1 << std::endl;
    out << "Player 2: " << player2 << std::endl;
    out << "Trade Area: " << tradeArea << std::endl;
    out << "Discard Pile: " << discardPile << std::endl;
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