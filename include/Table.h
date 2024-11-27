#ifndef TABLE_H
#define TABLE_H

#include <array>
#include <memory>
#include "Player.h"
#include "Deck.h"
#include "DiscardPile.h"
#include "TradeArea.h"

class Table
{
public:
    // Constructors
    Table(const std::string &player1Name, const std::string &player2Name);
    Table(std::istream &in, const CardFactory *factory);

    // Game state management
    bool win(std::string &winnerName);
    void printHand(bool all = false) const;

    // Getters with appropriate const overloads
    Player &getPlayer(int playerNum);
    const Player &getPlayer(int playerNum) const;
    Deck &getDeck() { return deck; }
    const Deck &getDeck() const { return deck; }
    DiscardPile &getDiscardPile() { return discardPile; }
    const DiscardPile &getDiscardPile() const { return discardPile; }
    TradeArea &getTradeArea() { return tradeArea; }
    const TradeArea &getTradeArea() const { return tradeArea; }

    // Player management
    int getCurrentPlayer() const { return currentPlayer; }
    void nextPlayer() { currentPlayer = (currentPlayer % 2) + 1; }

    // Serialization
    void saveGame(std::ostream &out) const;

    // Stream operator
    friend std::ostream &operator<<(std::ostream &out, const Table &table);

    // Destructor can be defaulted due to smart pointers
    ~Table() = default;

private:
    std::array<std::unique_ptr<Player>, 2> players;
    Deck deck;
    DiscardPile discardPile;
    TradeArea tradeArea;
    int currentPlayer = 1;

    void validatePlayerNum(int playerNum) const;
};

#endif // TABLE_H