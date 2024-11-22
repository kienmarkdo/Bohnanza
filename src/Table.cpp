#include "Table.h"
// Constructor: Creates a new table for a new game
Table::Table(const std::string &name1, const std::string &name2, const CardFactory *factory)
    : player1(name1), player2(name2), deck(factory->getDeck()), discardPile(), tradeArea() {}

// Constructor: Reconstructs the Table from a file
Table::Table(std::istream &in, const CardFactory *factory)
    : player1(in, factory), player2(in, factory), deck(in, factory), discardPile(in, factory), tradeArea(in, factory) {}

// Checks if the game has been won
bool Table::win(std::string &winnerName) const
{
    // The game is won if the deck is empty
    if (!deck.empty())
    {
        return false; // Game is not over if the deck still has cards
    }

    // Compare the number of coins for both players
    if (player1.getNumCoins() > player2.getNumCoins())
    {
        winnerName = player1.getName();
    }
    else if (player2.getNumCoins() > player1.getNumCoins())
    {
        winnerName = player2.getName();
    }
    else
    {
        winnerName = "Tie";
    }

    return true; // Game is over
}

// Prints the player's hand (top card or full hand)
void Table::printHand(bool showAll) const
{
    std::cout << player1.getName() << "'s hand: ";
    player1.printHand(std::cout, showAll);
    std::cout << std::endl;

    std::cout << player2.getName() << "'s hand: ";
    player2.printHand(std::cout, showAll);
    std::cout << std::endl;
}

// Draws a card from the deck
Card *Table::drawCard()
{
    return deck.draw();
}

// Stream insertion operator to print the Table
std::ostream &operator<<(std::ostream &out, const Table &table)
{
    out << "Player 1: " << table.player1 << std::endl;
    out << "Player 2: " << table.player2 << std::endl;
    out << "Deck size: " << table.deck.size() << std::endl;
    out << "Discard Pile: ";
    table.discardPile.print(out);
    out << std::endl;
    out << "Trade Area: " << table.tradeArea << std::endl;

    return out;
}