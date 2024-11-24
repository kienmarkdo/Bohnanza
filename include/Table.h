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
    // Constructor with player names
    Table(const std::string &player1Name, const std::string &player2Name);

    // Constructor to reconstruct table from file
    Table(std::istream &in, const CardFactory *factory);

    // Check for winner
    bool win(std::string &winnerName);

    // Print hand (true for all cards, false for top)
    void printHand(bool all = false) const;

    // Stream insertion operator
    friend std::ostream &operator<<(std::ostream &out, const Table &table);

    // Game state access methods
    Player &getPlayer(int playerNum);
    const Player &getPlayer(int playerNum) const;
    Deck &getDeck() { return deck; }
    DiscardPile &getDiscardPile() { return discardPile; }
    TradeArea &getTradeArea() { return tradeArea; }

    // Current player management
    int getCurrentPlayer() const { return currentPlayer; }
    void nextPlayer() { currentPlayer = (currentPlayer % 2) + 1; }

    // Save game state
    void saveGame(std::ostream &out) const;
    ~Table()
    {
        std::cout << "Table destructor start\n";
        try
        {
            std::cout << "Clearing players...\n";

            std::cout << "Clearing player 0...\n";
            if (players[0])
            {
                players[0].reset();
            }
            std::cout << "Player 0 cleared\n";

            std::cout << "Clearing player 1...\n";
            if (players[1])
            {
                players[1].reset();
            }
            std::cout << "Player 1 cleared\n";

            std::cout << "Clearing deck...\n";
            deck.clear();
            std::cout << "Deck cleared\n";

            std::cout << "Clearing discard pile...\n";
            discardPile = DiscardPile();
            std::cout << "Discard pile cleared\n";

            std::cout << "Clearing trade area...\n";
            tradeArea = TradeArea();
            std::cout << "Trade area cleared\n";
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error in Table destructor: " << e.what() << "\n";
        }
        std::cout << "Table destructor end\n";
    }

private:
    std::array<std::unique_ptr<Player>, 2> players;
    Deck deck;
    DiscardPile discardPile;
    TradeArea tradeArea;
    int currentPlayer = 1; // 1 or 2

    // Helper to validate player number
    void validatePlayerNum(int playerNum) const;
};

#endif // TABLE_H