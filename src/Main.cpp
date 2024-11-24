#include <fstream>   // For ofstream
#include <iostream>  // For cout, cin
#include <string>    // For string
#include <limits>    // For numeric_limits
#include <stdexcept> // For runtime_error
#include "CardFactory.h"
#include "Table.h"

bool getUserChoice(const std::string &prompt)
{
    std::string input;
    while (true)
    {
        std::cout << prompt << " (y/n): ";

        if (!std::getline(std::cin, input))
        {
            // Handle EOF or input error
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        // Trim whitespace
        input.erase(0, input.find_first_not_of(" \t\n\r\f\v"));
        input.erase(input.find_last_not_of(" \t\n\r\f\v") + 1);

        if (input.length() == 1)
        {
            char choice = std::tolower(input[0]);
            if (choice == 'y')
                return true;
            if (choice == 'n')
                return false;
        }

        std::cout << "Invalid input. Please enter 'y' or 'n'.\n";
    }
}
// Helper function to clear screen
void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int main()
{
    // clearScreen();
    std::cout << "=== Bean Trading Card Game ===\n\n";

    // Add debug output
    std::cout << "Creating CardFactory...\n";
    CardFactory *factory = CardFactory::getFactory();

    // Get player names
    std::string player1, player2;
    std::cout << "Enter name for Player 1: ";
    std::getline(std::cin, player1);
    std::cout << "Enter name for Player 2: ";
    std::getline(std::cin, player2);

    std::cout << "Creating game table...\n";
    std::unique_ptr<Table> gameTable = std::make_unique<Table>(player1, player2);
    std::cout << "Creating initial deck...\n";
    Deck initialDeck = factory->getDeck();
    std::cout << "Initial deck size: " << initialDeck.size() << "\n";

    // Set the deck in the table
    gameTable->getDeck() = factory->getDeck();

    // Deal initial hands
    std::cout << "Dealing initial hands...\n";
    for (int i = 0; i < 5; ++i)
    {
        if (gameTable->getDeck().empty())
        {
            std::cout << "Error: Deck empty while dealing initial hands\n";
            break;
        }
        Card *card1 = gameTable->getDeck().draw();
        Card *card2 = gameTable->getDeck().draw();
        if (!card1 || !card2)
        {
            std::cout << "Error: Null card drawn\n";
            break;
        }
        gameTable->getPlayer(1).addToHand(card1);
        gameTable->getPlayer(2).addToHand(card2);
    }

    // Main game loop
    while (gameTable && !gameTable->getDeck().empty())
    // ... rest of game lo
    {
        // clearScreen();
        std::cout << *gameTable; // Display current game state

        // Get current player
        Player &currentPlayer = gameTable->getPlayer(gameTable->getCurrentPlayer());
        std::cout << "\n=== " << currentPlayer.getName() << "'s Turn ===\n";

        // Check for pause
        if (getUserChoice("Would you like to pause and save the game?"))
        {
            std::string filename;
            std::cout << "Enter filename to save: ";
            std::getline(std::cin, filename);
            try
            {
                {
                    std::ofstream saveFile(filename);
                    if (!saveFile.is_open())
                    {
                        throw std::runtime_error("Could not open file for saving: " + filename);
                    }
                    gameTable->saveGame(saveFile);
                    saveFile.close();
                }

                std::cout << "Game saved successfully!\n";

                if (!getUserChoice("Would you like to continue playing?"))
                {
                    std::cout << "Starting cleanup...\n";

                    // Cleanup in proper order
                    if (gameTable)
                    {
                        std::cout << "Clearing game table...\n";
                        // Clear the table before cleaning up factory
                        gameTable.reset();
                    }

                    std::cout << "Game table cleared\n";
                    return 0;
                }
            }
            catch (const std::exception &e)
            {
                std::cerr << "Error during save: " << e.what() << "\n";
                return 1;
            }
        }

        // 1. Draw top card from deck
        if (!gameTable->getDeck().empty())
        {
            Card *drawnCard = gameTable->getDeck().draw();
            if (drawnCard)
            { // Add null check
                std::cout << "\nDrawn card: " << *drawnCard << "\n";
                currentPlayer.addToHand(drawnCard); // Keep using currentPlayer
            }
        }

        // 2. Process trade area from previous turn
        if (!gameTable->getTradeArea().empty())
        {
            std::cout << "\nCurrent trade area: " << gameTable->getTradeArea() << "\n";
            while (!gameTable->getTradeArea().empty() &&
                   getUserChoice("Would you like to add a card from the trade area to your chains?"))
            {
                std::cout << "Available beans in trade area:\n";
                for (const auto &card : gameTable->getTradeArea())
                {
                    std::cout << card->getName() << " ";
                }
                std::cout << "\nEnter bean name to chain (or 'skip' to move on): ";
                std::string beanName;
                std::getline(std::cin, beanName);
                if (beanName == "skip")
                    break;

                try
                {
                    Card *tradedCard = gameTable->getTradeArea().trade(beanName);
                    // Add to appropriate chain or create new one
                    // This is simplified; you'd need to handle chain selection/creation
                    std::cout << "Card chained.\n";
                }
                catch (const std::exception &e)
                {
                    std::cout << "Error: " << e.what() << "\n";
                }
            }
        }

        // 3. Play top card from hand
        try
        {
            Card *playedCard = currentPlayer.playFromHand();
            std::cout << "\nPlayed card: " << *playedCard << "\n";
            // Add to appropriate chain logic here
        }
        catch (const std::exception &e)
        {
            std::cout << "Error playing card: " << e.what() << "\n";
        }

        // 4. Optional: Play second card
        if (getUserChoice("\nWould you like to play another card?"))
        {
            try
            {
                Card *playedCard = currentPlayer.playFromHand();
                std::cout << "Played card: " << *playedCard << "\n";
                // Add to appropriate chain logic here
            }
            catch (const std::exception &e)
            {
                std::cout << "Error playing card: " << e.what() << "\n";
            }
        }

        // 5. Optional: Discard a card
        if (getUserChoice("\nWould you like to discard a card?"))
        {
            currentPlayer.printHand(std::cout, true);
            std::cout << "Enter index of card to discard: ";
            int index;
            std::cin >> index;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            try
            {
                Card *discardedCard = currentPlayer.getCardFromHand(index);
                gameTable->getDiscardPile() += discardedCard;
                std::cout << "Card discarded.\n";
            }
            catch (const std::exception &e)
            {
                std::cout << "Error discarding card: " << e.what() << "\n";
            }
        }

        // 6. Draw and process trade cards
        for (int i = 0; i < 3 && !gameTable->getDeck().empty(); ++i)
        {
            gameTable->getTradeArea() += gameTable->getDeck().draw();
        }

        // Process matching cards from discard pile
        while (!gameTable->getDiscardPile().empty() &&
               gameTable->getTradeArea().legal(gameTable->getDiscardPile().top()))
        {
            gameTable->getTradeArea() += gameTable->getDiscardPile().pickUp();
        }

        // 7. Draw two cards for hand
        for (int i = 0; i < 2 && !gameTable->getDeck().empty(); ++i)
        {
            currentPlayer.addToHand(gameTable->getDeck().draw());
        }

        // Move to next player
        gameTable->nextPlayer();

        std::cout << "\nPress Enter to continue...";
        std::cin.get();
    }

    // Game is over, determine winner
    std::string winnerName;
    if (gameTable->win(winnerName))
    {
        std::cout << "\nGame Over! The winner is: " << winnerName << "!\n";
    }
    else
    {
        std::cout << "\nGame Over! It's a tie!\n";
    }

    return 0;
}