#include <iostream>
#include <fstream>
#include <string>
#include "Player.h"
#include "Table.h"
#include "CardFactory.h"

int main()
{
    CardFactory *factory = CardFactory::getFactory();
    Table *table = nullptr;

    // Prompt the user to load a saved game or start a new one
    std::cout << "Load saved game? (y/n): ";
    char choice;
    std::cin >> choice;

    if (choice == 'y')
    {
        // Load game from file
        std::ifstream inFile("saved_game.txt");
        if (inFile.is_open())
        {
            table = new Table(inFile, factory); // Assuming Table supports file-based reconstruction
            inFile.close();
            std::cout << "Game successfully loaded.\n";
        }
        else
        {
            std::cerr << "Error: Could not open saved game file.\n";
            return 1;
        }
    }
    else
    {
        std::string player1Name, player2Name;

        // Input player names
        std::cout << "Enter Player 1 name: ";
        std::cin >> player1Name;
        std::cout << "Enter Player 2 name: ";
        std::cin >> player2Name;

        // Initialize the Table with players and a shuffled deck
        table = new Table(player1Name, player2Name, factory);

        // Deal 5 cards to each player's hand
        for (int i = 0; i < 5; ++i)
        {
            table->getPlayer1().hand += table->drawCard(); // Directly access hand
            table->getPlayer2().hand += table->drawCard();
        }

        std::cout << "New game successfully started.\n";
    }

    // Main game loop
    while (!table->deck.empty())
    { // Directly check the deck
        // Check for pause and save functionality
        std::cout << "Pause game? (y/n): ";
        std::cin >> choice;
        if (choice == 'y')
        {
            std::ofstream outFile("saved_game.txt");
            table->save(outFile);
            outFile.close();
            std::cout << "Game saved. Exiting...\n";
            delete table;
            delete factory;
            return 0;
        }

        // Player turns
        for (int i = 0; i < 2; ++i)
        {
            Player &currentPlayer = table->getPlayer(i);

            std::cout << "\n--- " << currentPlayer.getName() << "'s Turn ---\n";

            // Display the table
            std::cout << *table;

            // Draw a card from the deck
            Card *drawnCard = table->drawCard();
            currentPlayer.addCardToHand(drawnCard);

            // Handle TradeArea
            while (table->isTradeAreaNotEmpty())
            {
                Card *tradeCard = table->getTradeAreaCard();
                if (currentPlayer.canChainCard(tradeCard))
                {
                    currentPlayer.addToChain(tradeCard);
                }
                else
                {
                    table->discardCard(tradeCard);
                }
            }

            // Player plays topmost card from hand
            Card *topCard = currentPlayer.playTopCard();
            if (topCard)
            {
                if (currentPlayer.canChainCard(topCard))
                {
                    currentPlayer.addToChain(topCard);
                }
                else
                {
                    // Player creates a new chain
                    std::cout << "No matching chain. Starting a new chain.\n";
                    currentPlayer.addNewChain(topCard);
                }
            }

            // Additional player actions
            char actionChoice;
            std::cout << "Play another card from hand? (y/n): ";
            std::cin >> actionChoice;
            if (actionChoice == 'y')
            {
                Card *nextTopCard = currentPlayer.playTopCard();
                if (nextTopCard)
                {
                    if (currentPlayer.canChainCard(nextTopCard))
                    {
                        currentPlayer.addToChain(nextTopCard);
                    }
                    else
                    {
                        std::cout << "No matching chain. Starting a new chain.\n";
                        currentPlayer.addNewChain(nextTopCard);
                    }
                }
            }

            // Show hand and discard a card
            std::cout << "Show hand? (y/n): ";
            std::cin >> actionChoice;
            if (actionChoice == 'y')
            {
                currentPlayer.printHand(std::cout, true);
                std::cout << "\nSelect a card to discard by index: ";
                int index;
                std::cin >> index;
                Card *discardedCard = currentPlayer.discardCard(index);
                if (discardedCard)
                {
                    table->discardCard(discardedCard);
                }
            }

            // Draw three cards from deck into the TradeArea
            for (int j = 0; j < 3; ++j)
            {
                Card *tradeCard = table->drawCard();
                if (tradeCard)
                {
                    table->addCardToTradeArea(tradeCard);
                }
            }

            // Handle top cards of discard pile matching TradeArea
            while (table->discardPileMatchesTradeArea())
            {
                Card *discardedCard = table->pickUpFromDiscardPile();
                table->addCardToTradeArea(discardedCard);
            }

            // Chain or leave cards in TradeArea
            table->handleTradeAreaForPlayer(currentPlayer);

            // Draw two cards from deck for the player
            for (int j = 0; j < 2; ++j)
            {
                Card *newCard = table->drawCard();
                if (newCard)
                {
                    currentPlayer.addCardToHand(newCard);
                }
            }
        }
    }

    // End game
    std::string winnerName;
    if (table->win(winnerName))
    {
        std::cout << "Game over! The winner is: " << winnerName << "\n";
    }
    else
    {
        std::cout << "Game over! It's a tie!\n";
    }

    delete table;
    delete factory;
    return 0;
}