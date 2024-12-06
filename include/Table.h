#ifndef TABLE_H
#define TABLE_H

#include <array>
#include <memory>
#include "Player.h"
#include "Deck.h"
#include "DiscardPile.h"
#include "TradeArea.h"

/**
 * @brief Represents the game table that manages the overall state of the game
 * @details The Table class coordinates all game components including players,
 *          deck, discard pile, and trade area. It manages turn order and game flow.
 */
class Table
{
public:
    /**
     * @brief Constructs a new game table with two players
     * @param player1Name The name of the first player
     * @param player2Name The name of the second player
     */
    Table(const std::string &player1Name, const std::string &player2Name);

    /**
     * @brief Constructs a table from a saved game state
     * @param in Input stream containing the saved game state
     * @param factory Pointer to the card factory for card creation
     */
    Table(std::istream &in, const CardFactory *factory);

    /**
     * @brief Checks if the game has been won
     * @param winnerName Reference to store the winner's name
     * @return true if there is a winner, false otherwise
     */
    bool win(std::string &winnerName);

    /**
     * @brief Prints the current player's hand
     * @param all If true, prints all players' hands, otherwise only current player
     */
    void printHand(bool all = false) const;

    /**
     * @brief Gets a reference to a player
     * @param playerNum Player number (1 or 2)
     * @return Reference to the specified player
     * @throws std::out_of_range if playerNum is invalid
     */
    Player &getPlayer(int playerNum);
    const Player &getPlayer(int playerNum) const;

    /** @brief Gets the deck */
    Deck &getDeck() { return deck; }
    const Deck &getDeck() const { return deck; }

    /** @brief Gets the discard pile */
    DiscardPile &getDiscardPile() { return discardPile; }
    const DiscardPile &getDiscardPile() const { return discardPile; }

    /** @brief Gets the trade area */
    TradeArea &getTradeArea() { return tradeArea; }
    const TradeArea &getTradeArea() const { return tradeArea; }

    /**
     * @brief Gets the current player's number
     * @return Current player number (1 or 2)
     */
    int getCurrentPlayer() const { return currentPlayer; }

    /**
     * @brief Advances to the next player's turn
     */
    void nextPlayer() { currentPlayer = (currentPlayer % 2) + 1; }

    /**
     * @brief Saves the current game state
     * @param out Output stream to save the game state
     */
    void saveGame(std::ostream &out) const;

    /**
     * @brief Outputs the table state to a stream
     * @param out Output stream
     * @param table Table to output
     * @return Reference to the output stream
     */
    friend std::ostream &operator<<(std::ostream &out, const Table &table);

    /** @brief Default destructor */
    ~Table() = default;

private:
    std::array<std::unique_ptr<Player>, 2> players; ///< Array of player pointers
    Deck deck;                                      ///< Game deck
    DiscardPile discardPile;                        ///< Discard pile
    TradeArea tradeArea;                            ///< Trade area
    int currentPlayer = 1;                          ///< Current player number (1 or 2)

    /**
     * @brief Validates player number
     * @param playerNum Player number to validate
     * @throws std::out_of_range if playerNum is invalid
     */
    void validatePlayerNum(int playerNum) const;
};

#endif // TABLE_H
