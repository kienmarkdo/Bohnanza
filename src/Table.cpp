#include "Table.h"
#include <stdexcept>
#include <sstream>
#include <limits>
#include "CardFactory.h"

/**
 * @brief Constructs a new game table with two players
 *
 * @param player1Name Name of the first player
 * @param player2Name Name of the second player
 *
 * Initializes a new game with empty deck, discard pile, and trade area.
 * Sets player 1 as the current player.
 */
Table::Table(const std::string &player1Name, const std::string &player2Name)
{
    players[0] = std::make_unique<Player>(player1Name);
    players[1] = std::make_unique<Player>(player2Name);
    currentPlayer = 1;
}

/**
 * @brief Constructs a Table from a saved game state
 *
 * @param in Input stream containing serialized table data
 * @param factory Pointer to the CardFactory used to create cards
 *
 * Reads and reconstructs:
 * - Current player
 * - Both players' states
 * - Deck
 * - Discard pile
 * - Trade area
 */
Table::Table(std::istream &in, const CardFactory *factory)
{
    // Load current player number
    in >> currentPlayer;
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Load Player 1
    players[0] = std::make_unique<Player>(in, factory);
    // Load Player 2
    players[1] = std::make_unique<Player>(in, factory);

    // Load Deck
    Deck loadedDeck(in, factory);
    deck = std::move(loadedDeck);

    // Load Discard Pile
    DiscardPile loadedDiscard(in, factory);
    discardPile = std::move(loadedDiscard);

    // Load Trade Area
    TradeArea loadedTrade(in, factory);
    tradeArea = std::move(loadedTrade);
}

/**
 * @brief Validates if a player number is valid (1 or 2)
 *
 * @param playerNum Player number to validate
 * @throws std::out_of_range if player number is invalid
 */
void Table::validatePlayerNum(int playerNum) const
{
    if (playerNum < 1 || playerNum > 2)
    {
        throw std::out_of_range("Invalid player number: " +
                                std::to_string(playerNum) + ". Must be 1 or 2.");
    }
}

/**
 * @brief Gets a reference to a player by their number
 *
 * @param playerNum Player number (1 or 2)
 * @return Reference to the Player object
 * @throws std::out_of_range if player number is invalid
 */
Player &Table::getPlayer(int playerNum)
{
    validatePlayerNum(playerNum);
    return *players[playerNum - 1];
}

/**
 * @brief Gets a const reference to a player by their number
 *
 * @param playerNum Player number (1 or 2)
 * @return Const reference to the Player object
 * @throws std::out_of_range if player number is invalid
 */
const Player &Table::getPlayer(int playerNum) const
{
    validatePlayerNum(playerNum);
    return *players[playerNum - 1];
}

/**
 * @brief Checks if the game is over and determines the winner
 *
 * @param winnerName String to store the winner's name
 * @return true if game is over (deck is empty), false otherwise
 *
 * Winner is determined by the player with the most coins when
 * the deck becomes empty. In case of a tie, player 1 wins.
 */
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

/**
 * @brief Prints the current player's hand
 *
 * @param all If true, prints all cards; if false, only prints top card
 */
void Table::printHand(bool all) const
{
    std::cout << "Current player (" << getPlayer(currentPlayer).getName() << ")'s hand:\n";
    getPlayer(currentPlayer).printHand(std::cout, all);
}

/**
 * @brief Saves the current game state to a stream
 *
 * @param out Output stream to save to
 *
 * Saves:
 * - Current player number
 * - Both players' states
 * - Deck state
 * - Discard pile state
 * - Trade area state
 */
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

/**
 * @brief Stream insertion operator for Table
 *
 * @param out Output stream
 * @param table Table to output
 * @return Reference to the output stream
 *
 * Prints formatted view of current game state including:
 * - Both players' states
 * - Trade area
 * - Discard pile
 */
std::ostream &operator<<(std::ostream &out, const Table &table)
{
    out << "=== Player 1: " << table.getPlayer(1).getName() << " ===" << "\n";
    out << table.getPlayer(1) << "\n";

    out << "=== Player 2: " << table.getPlayer(2).getName() << " ===" << "\n";
    out << table.getPlayer(2) << "\n";

    out << "=== Trading Area ===" << "\n";
    out << table.getTradeArea() << "\n";

    out << "=== Discard Pile ===" << "\n";
    table.getDiscardPile().print(out);

    return out;
}