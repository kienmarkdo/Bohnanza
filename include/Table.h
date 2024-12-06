#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include <string>
#include "Player.h"
#include "Deck.h"
#include "DiscardPile.h"
#include "TradeArea.h"

class CardFactory;

class Table {
private:
    Player player1;
    Player player2;
    Deck deck;
    DiscardPile discardPile;
    TradeArea tradeArea;
public:
    Table(const std::string& p1Name, const std::string& p2Name, Deck&& initialDeck);
    Table(std::istream& in, CardFactory* factory);

    Player& getPlayer1() { return player1; }
    Player& getPlayer2() { return player2; }
    Deck& getDeck() { return deck; }
    DiscardPile& getDiscardPile() { return discardPile; }
    TradeArea& getTradeArea() { return tradeArea; }

    friend std::ostream& operator<<(std::ostream& out, const Table& table);
};

#endif
