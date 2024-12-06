#include <iostream>
#include <fstream>
#include "Table.h"
#include "CardFactory.h"

int main() {
    // Setting up the game with two players
    std::string player1Name, player2Name;

    std::cout << "Enter Player 1 Name: ";
    std::cin >> player1Name;
    Player player1(player1Name);

    std::cout << "Enter Player 2 Name: ";
    std::cin >> player2Name;
    Player player2(player2Name);

    // Set up CardFactory and Table
    CardFactory* factory = CardFactory::getFactory();
    Table table(player1, player2);

    // Main game loop
    while (table.getDeck().size() > 0 && !table.win(player1) && !table.win(player2)) {
        std::cout << "\nCurrent Table State:\n";
        table.print(std::cout);

        // Player 1 turn
        std::cout << "\n" << player1.getName() << "'s turn:\n";
        Card* drawnCard = table.getDeck().draw();
        if (drawnCard) {
            std::cout << "You drew: " << *drawnCard << std::endl;
            table.addCardToTradeArea(drawnCard);
        }

        // Player can decide what to do with trade area cards
        std::cout << table.getTradeArea() << std::endl;

        // Player 2 turn (similar steps as Player 1)
        std::cout << "\n" << player2.getName() << "'s turn:\n";
        drawnCard = table.getDeck().draw();
        if (drawnCard) {
            std::cout << "You drew: " << *drawnCard << std::endl;
            table.addCardToTradeArea(drawnCard);
        }

        // Player can decide what to do with trade area cards
        std::cout << table.getTradeArea() << std::endl;

        // End of game conditions
        if (table.win(player1)) {
            std::cout << player1.getName() << " wins the game!" << std::endl;
            break;
        } else if (table.win(player2)) {
            std::cout << player2.getName() << " wins the game!" << std::endl;
            break;
        }
    }

    return 0;
}
