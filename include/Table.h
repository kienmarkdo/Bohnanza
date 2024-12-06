#ifndef TABLE_H
#define TABLE_H

#include <vector>
#include "Player.h"
#include "Deck.h"
#include "DiscardPile.h"
#include "TradeArea.h"

class Table {
public:
    Table(Player& player1, Player& player2);
    bool win(const Player& player) const;
    void print(std::ostream& out) const;
    void addCardToTradeArea(Card* card);
    DiscardPile& getDiscardPile();
    TradeArea& getTradeArea();
    Deck& getDeck();

private:
    Player& player1;
    Player& player2;
    Deck deck;
    DiscardPile discardPile;
    TradeArea tradeArea;
};

#endif // TABLE_H
