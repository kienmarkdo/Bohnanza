#include "Table.h"
#include <stdexcept>
#include <sstream>

Table::Table(const std::string &player1Name, const std::string &player2Name)
{
    // Create players
    try
    {
        players[0] = std::make_unique<Player>(player1Name);
        players[1] = std::make_unique<Player>(player2Name);
        currentPlayer = 1;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error in Table constructor: " << e.what() << "\n";
        throw;
    }
}

Table::Table(std::istream &in, const CardFactory *factory)
{
    // Implementation will be completed when CardFactory is implemented
    // This constructor will read the table state from a file and reconstruct it

    // For now, create empty table
    players[0] = std::make_unique<Player>("Player1");
    players[1] = std::make_unique<Player>("Player2");
}

void Table::validatePlayerNum(int playerNum) const
{
    if (playerNum < 1 || playerNum > 2)
    {
        std::ostringstream oss;
        oss << "Invalid player number: " << playerNum << ". Must be 1 or 2.";
        throw std::out_of_range(oss.str());
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
    // Check if deck is empty
    if (!deck.empty())
    {
        return false;
    }

    // Game is over, determine winner based on coins
    int coins1 = players[0]->getNumCoins();
    int coins2 = players[1]->getNumCoins();

    if (coins1 > coins2)
    {
        winnerName = players[0]->getName();
        return true;
    }
    else if (coins2 > coins1)
    {
        winnerName = players[1]->getName();
        return true;
    }
    else
    {
        // In case of tie, return first player's name
        winnerName = players[0]->getName();
        return true;
    }
}

void Table::printHand(bool all) const
{
    std::cout << "Current player (" << getPlayer(currentPlayer).getName() << ")'s hand:\n";
    getPlayer(currentPlayer).printHand(std::cout, all);
}

std::ostream &operator<<(std::ostream &out, const Table &table)
{
    out << "=== Initial State ===\n";

    // Print Player 1's hand
    out << table.getPlayer(1).getName() << "'s Hand: ";
    table.getPlayer(1).printHand(out, true);
    out << "\n";

    // Print Player 2's hand
    out << table.getPlayer(2).getName() << "'s Hand: ";
    table.getPlayer(2).printHand(out, true);
    out << "\n";

    // Print Trade Area
    out << "Trade Area: ";
    if (table.tradeArea.numCards() == 0)
    {
        out << "(empty)";
    }
    else
    {
        out << table.tradeArea;
    }
    out << "\n";

    // Print Discard Pile
    out << "Discard Pile: ";
    if (table.discardPile.empty())
    {
        out << "(empty)";
    }
    else
    {
        out << table.discardPile;
    }
    out << "\n";

    // Print current player
    out << "Current player: " << table.getPlayer(table.getCurrentPlayer()).getName();
    out << "\n";

    return out;
}
void Table::saveGame(std::ostream &out) const
{
    try
    {
        std::cout << "Starting save...\n";

        // Save current player
        out << currentPlayer << "\n";
        std::cout << "Saved current player\n";

        // Save players
        for (const auto &player : players)
        {
            if (player)
            {
                player->serialize(out);
                std::cout << "Saved player\n";
            }
        }

        // Save deck
        std::cout << "Saving deck...\n";
        deck.serialize(out);
        std::cout << "Deck saved\n";

        // Save discard pile
        std::cout << "Saving discard pile...\n";
        discardPile.serialize(out);
        std::cout << "Discard pile saved\n";

        // Save trade area
        std::cout << "Saving trade area...\n";
        tradeArea.serialize(out);
        std::cout << "Trade area saved\n";

        std::cout << "Save completed successfully\n";
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error during save: " << e.what() << std::endl;
        throw; // Re-throw the exception
    }
}