#include "Table.h"
#include <stdexcept>
#include <sstream>
#include <limits>
#include "CardFactory.h"

Table::Table(const std::string &player1Name, const std::string &player2Name) {
    players[0] = std::make_unique<Player>(player1Name);
    players[1] = std::make_unique<Player>(player2Name);
    currentPlayer = 1;
}

// Updated constructor to load from file
Table::Table(std::istream &in, const CardFactory *factory) {
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

void Table::validatePlayerNum(int playerNum) const {
    if (playerNum < 1 || playerNum > 2) {
        throw std::out_of_range("Invalid player number: " +
                                std::to_string(playerNum) + ". Must be 1 or 2.");
    }
}

Player &Table::getPlayer(int playerNum) {
    validatePlayerNum(playerNum);
    return *players[playerNum - 1];
}

const Player &Table::getPlayer(int playerNum) const {
    validatePlayerNum(playerNum);
    return *players[playerNum - 1];
}

bool Table::win(std::string &winnerName) {
    if (!deck.empty()) {
        return false;
    }

    int coins1 = players[0]->getNumCoins();
    int coins2 = players[1]->getNumCoins();

    if (coins1 >= coins2) {
        winnerName = players[0]->getName();
    } else {
        winnerName = players[1]->getName();
    }
    return true;
}

void Table::printHand(bool all) const {
    std::cout << "Current player (" << getPlayer(currentPlayer).getName() << ")'s hand:\n";
    getPlayer(currentPlayer).printHand(std::cout, all);
}

void Table::saveGame(std::ostream &out) const {
    out << currentPlayer << "\n";

    for (const auto &player : players) {
        if (player) {
            player->serialize(out);
        }
    }

    deck.serialize(out);
    discardPile.serialize(out);
    tradeArea.serialize(out);
}

std::ostream &operator<<(std::ostream &out, const Table &table) {
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
