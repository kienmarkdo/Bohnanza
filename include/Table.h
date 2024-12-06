// Table.h (Updates for save/load functionality)
#ifndef TABLE_H
#define TABLE_H

#include "Player.h"
#include "Deck.h"
#include "DiscardPile.h"
#include "TradeArea.h"
#include <iostream>

class Table {
public:
    Table(Player& p1, Player& p2);
    bool win(const Player& player) const;
    void print(std::ostream& out) const;
    void addCardToTradeArea(Card* card);

    // Getters
    DiscardPile& getDiscardPile();
    TradeArea& getTradeArea();
    Deck& getDeck();

    // Save and load game state
    friend std::ostream& operator<<(std::ostream& out, const Table& table);
    friend std::istream& operator>>(std::istream& in, Table& table);

private:
    Player& player1;
    Player& player2;
    Deck deck;
    DiscardPile discardPile;
    TradeArea tradeArea;
};

#endif // TABLE_H
