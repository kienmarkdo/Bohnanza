#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include <string>
#include "Player.h"
#include "Deck.h"
#include "DiscardPile.h"
#include "TradeArea.h"
#include "CardFactory.h"

class Table
{
private:
    Player player1;          // First player
    Player player2;          // Second player
    Deck deck;               // Deck of cards
    DiscardPile discardPile; // Discard pile
    TradeArea tradeArea;     // Trade area

public:
    // Constructor: Creates a new table for a new game
    Table(const std::string &name1, const std::string &name2, const CardFactory *factory);

    // Constructor: Reconstructs the Table from a file
    Table(std::istream &in, const CardFactory *factory);

    // Checks if the game has been won
    bool win(std::string &winnerName) const;

    Player &getPlayer1() { return player1; }
    Player &getPlayer2() { return player2; }

    // Prints the player's hand (top card or full hand)
    void printHand(bool showAll) const;

    // Draws a card from the deck
    Card *drawCard();

    // Stream insertion operator to print the Table
    friend std::ostream &operator<<(std::ostream &out, const Table &table);
};

#endif // TABLE_H