#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include <string>
#include "Player.h"
#include "Deck.h"
#include "DiscardPile.h"
#include "TradeArea.h"

class Table {
private:
    Player player1;
    Player player2;
    Deck deck;
    DiscardPile discardPile;
    TradeArea tradeArea;
public:
    Table(const std::string& p1Name, const std::string& p2Name, Deck&& initialDeck)
        : player1(p1Name), player2(p2Name), deck(std::move(initialDeck)) {}

    // Returns true if game is over (deck is empty)
    bool win() const;

    // Get player references
    Player& getPlayer1() { return player1; }
    Player& getPlayer2() { return player2; }

    Deck& getDeck() { return deck; }
    DiscardPile& getDiscardPile() { return discardPile; }
    TradeArea& getTradeArea() { return tradeArea; }

    // Print table: print top card of deck face down (?), print discard pile, trade area, and each player.
    // Adjust format as per specs.
    friend std::ostream& operator<<(std::ostream& out, const Table& table);
};

#endif
