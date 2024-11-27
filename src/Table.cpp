#include "Table.h"
#include <stdexcept>
#include <sstream>

Table::Table(const std::string &player1Name, const std::string &player2Name)
{
    players[0] = std::make_unique<Player>(player1Name);
    players[1] = std::make_unique<Player>(player2Name);
    currentPlayer = 1;
}

Table::Table(std::istream &in, const CardFactory *factory)
{
    // Load state from stream
    // Implementation will be updated when needed
    players[0] = std::make_unique<Player>("Player1");
    players[1] = std::make_unique<Player>("Player2");
}

void Table::validatePlayerNum(int playerNum) const
{
    if (playerNum < 1 || playerNum > 2)
    {
        throw std::out_of_range("Invalid player number: " +
                                std::to_string(playerNum) + ". Must be 1 or 2.");
    }
}

Player &Table::getPlayer(int playerNum)
{
    validatePlayerNum(playerNum);
    return *players[playerNum - 1];
}

const Player &Table::getPlayer(int playerNum) const
{
    validatePlayerNum(playerNum);
    return *players[playerNum - 1];
}

bool Table::win(std::string &winnerName)
{
    if (!deck.empty())
    {
        return false;
    }

    int coins1 = players[0]->getNumCoins();
    int coins2 = players[1]->getNumCoins();

    if (coins1 >= coins2)
    {
        winnerName = players[0]->getName();
    }
    else
    {
        winnerName = players[1]->getName();
    }
    return true;
}

void Table::printHand(bool all) const
{
    std::cout << "Current player (" << getPlayer(currentPlayer).getName() << ")'s hand:\n";
    getPlayer(currentPlayer).printHand(std::cout, all);
}

void Table::saveGame(std::ostream &out) const
{
    out << currentPlayer << "\n";

    for (const auto &player : players)
    {
        if (player)
        {
            player->serialize(out);
        }
    }

    deck.serialize(out);
    discardPile.serialize(out);
    tradeArea.serialize(out);
}

std::ostream &operator<<(std::ostream &out, const Table &table)
{
    // Print both players
    out << "=== Player 1: " << table.getPlayer(1).getName() << " ===" << "\n";
    out << table.getPlayer(1) << "\n";

    out << "=== Player 2: " << table.getPlayer(2).getName() << " ===" << "\n";
    out << table.getPlayer(2) << "\n";

    // Print trading area with header
    out << "=== Trading Area ===" << "\n";
    out << table.getTradeArea() << "\n";

    // Print discard pile with header
    out << "=== Discard Pile ===" << "\n";
    out << table.getDiscardPile() << "\n";

    return out;
}