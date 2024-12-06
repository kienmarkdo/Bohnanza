#include <fstream>
#include <iostream>
#include <string>
#include <limits>
#include <stdexcept>
#include <memory>
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
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

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
    std::cout << "=== Bean Trading Card Game ===\n\n";

    std::cout << "Creating CardFactory...\n";
    auto factory = CardFactory::getFactory();

    std::string player1, player2;
    std::cout << "Enter name for Player 1: ";
    std::getline(std::cin, player1);
    std::cout << "Enter name for Player 2: ";
    std::getline(std::cin, player2);

    std::cout << "Creating game table...\n";
    auto gameTable = std::make_unique<Table>(player1, player2);
    std::cout << "Creating initial deck...\n";
    auto initialDeck = factory->getDeck();
    std::cout << "Initial deck size: " << initialDeck->size() << "\n";

    // Set the deck in the table
    gameTable->getDeck() = std::move(*initialDeck);

    // Deal initial hands
    std::cout << "Dealing initial hands...\n";
    for (int i = 0; i < 5; ++i)
    {
        if (gameTable->getDeck().empty())
        {
            std::cout << "Error: Deck empty while dealing initial hands\n";
            break;
        }

        auto card1 = gameTable->getDeck().draw();
        auto card2 = gameTable->getDeck().draw();

        if (card1 && card2)
        {
            gameTable->getPlayer(1).addToHand(std::move(card1));
            gameTable->getPlayer(2).addToHand(std::move(card2));
        }
        else
        {
            std::cout << "Error: Null card drawn\n";
            break;
        }
    }

    // Main game loop
    while (gameTable && !gameTable->getDeck().empty())
    {
        std::cout << *gameTable;

        Player &currentPlayer = gameTable->getPlayer(gameTable->getCurrentPlayer());
        std::cout << "\n=== " << currentPlayer.getName() << "'s Turn ===\n";

        // Save game logic
        if (getUserChoice("Would you like to pause and save the game?"))
        {
            std::string filename;
            std::cout << "Enter filename to save: ";
            std::getline(std::cin, filename);

            try
            {
                std::ofstream saveFile(filename);
                if (!saveFile)
                {
                    throw std::runtime_error("Could not open file for saving: " + filename);
                }
                gameTable->saveGame(saveFile);
                std::cout << "Game saved successfully!\n";

                if (!getUserChoice("Would you like to continue playing?"))
                {
                    std::cout << "Starting cleanup...\n";
                    gameTable.reset();
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

        // Draw phase
        if (!gameTable->getDeck().empty())
        {
            auto drawnCard = gameTable->getDeck().draw();
            if (drawnCard)
            {
                std::cout << "\nDrawn card: ";
                std::cout << drawnCard->getName();
                std::cout << "\n";
                currentPlayer.addToHand(std::move(drawnCard));
            }
        }
        if (currentPlayer.getNumCoins() >= 3 && currentPlayer.getMaxNumChains() == 2)
        {
            if (getUserChoice("Would you like to buy a third chain for 3 coins?"))
            {
                try
                {
                    currentPlayer.buyThirdChain();
                    std::cout << "Third chain purchased successfully!\n";
                }
                catch (const NotEnoughCoins &e)
                {
                    std::cout << "Error: Not enough coins to buy third chain.\n";
                }
                catch (const std::runtime_error &e)
                {
                    std::cout << "Error: " << e.what() << "\n";
                }
            }
        }
        // Trade area phase
        if (!gameTable->getTradeArea().empty())
        {
            std::cout << "\nCurrent trade area: " << gameTable->getTradeArea() << "\n";
            while (!gameTable->getTradeArea().empty() &&
                   getUserChoice("Would you like to add a card from the trade area to your chains?"))
            {
                std::cout << "Available beans in trade area: " << gameTable->getTradeArea() << "\n";
                std::cout << "Enter bean name to chain (or 'skip' to move on): ";
                std::string beanName;
                std::getline(std::cin, beanName);
                if (beanName == "skip")
                {
                    break;
                }
                try
                {
                    auto tradedCard = gameTable->getTradeArea().trade(beanName);

                    // Determine card type and add to appropriate chain
                    if (auto *stinkCard = dynamic_cast<Stink *>(tradedCard.get()))
                    {
                        currentPlayer.addCardToChain<Stink>(std::move(tradedCard));
                    }
                    else if (auto *blueCard = dynamic_cast<Blue *>(tradedCard.get()))
                    {
                        currentPlayer.addCardToChain<Blue>(std::move(tradedCard));
                    }
                    else if (auto *chiliCard = dynamic_cast<Chili *>(tradedCard.get()))
                    {
                        currentPlayer.addCardToChain<Chili>(std::move(tradedCard));
                    }
                    else if (auto *greenCard = dynamic_cast<Green *>(tradedCard.get()))
                    {
                        currentPlayer.addCardToChain<Green>(std::move(tradedCard));
                    }
                    else if (auto *soyCard = dynamic_cast<Soy *>(tradedCard.get()))
                    {
                        currentPlayer.addCardToChain<Soy>(std::move(tradedCard));
                    }
                    else if (auto *blackCard = dynamic_cast<Black *>(tradedCard.get()))
                    {
                        currentPlayer.addCardToChain<Black>(std::move(tradedCard));
                    }
                    else if (auto *redCard = dynamic_cast<Red *>(tradedCard.get()))
                    {
                        currentPlayer.addCardToChain<Red>(std::move(tradedCard));
                    }
                    else if (auto *gardenCard = dynamic_cast<Garden *>(tradedCard.get()))
                    {
                        currentPlayer.addCardToChain<Garden>(std::move(tradedCard));
                    }
                    else
                    {
                        throw std::runtime_error("Unknown card type");
                    }

                    std::cout << "Card chained.\n";
                }
                catch (const std::exception &e)
                {
                    std::cout << "Error: " << e.what() << "\n";
                }
            }
        }

        // Play cards phase
        try
        {
            auto playedCard = currentPlayer.playFromHand();
            std::cout << "\nPlayed card: ";
            std::cout << playedCard->getName();
            std::cout << "\n";
            try
            {
                if (auto *stinkCard = dynamic_cast<Stink *>(playedCard.get()))
                {
                    currentPlayer.addCardToChain<Stink>(std::move(playedCard));
                }
                else if (auto *blueCard = dynamic_cast<Blue *>(playedCard.get()))
                {
                    currentPlayer.addCardToChain<Blue>(std::move(playedCard));
                }
                else if (auto *chiliCard = dynamic_cast<Chili *>(playedCard.get()))
                {
                    currentPlayer.addCardToChain<Chili>(std::move(playedCard));
                }
                else if (auto *greenCard = dynamic_cast<Green *>(playedCard.get()))
                {
                    currentPlayer.addCardToChain<Green>(std::move(playedCard));
                }
                else if (auto *soyCard = dynamic_cast<Soy *>(playedCard.get()))
                {
                    currentPlayer.addCardToChain<Soy>(std::move(playedCard));
                }
                else if (auto *blackCard = dynamic_cast<Black *>(playedCard.get()))
                {
                    currentPlayer.addCardToChain<Black>(std::move(playedCard));
                }
                else if (auto *redCard = dynamic_cast<Red *>(playedCard.get()))
                {
                    currentPlayer.addCardToChain<Red>(std::move(playedCard));
                }
                else if (auto *gardenCard = dynamic_cast<Garden *>(playedCard.get()))
                {
                    currentPlayer.addCardToChain<Garden>(std::move(playedCard));
                }
                else
                {
                    throw std::runtime_error("Unknown card type");
                }
                std::cout << "Card chained.\n";
            }
            catch (const std::exception &e)
            {
                currentPlayer.addToFrontOfHand(std::move(playedCard)); // Need to implement this
                // std::cout << "Failed to create chain: " << e.what() << "\n";
            }
        }
        catch (const std::exception &e)
        {
            std::cout << "Error: " << e.what() << "\n";
        }

        // Optional second card
        if (getUserChoice("\nWould you like to play another card?"))
        {
            try
            {
                auto playedCard = currentPlayer.playFromHand();
                std::cout << "Played card: ";
                std::cout << playedCard->getName();
                std::cout << "\n";
                try
                {
                    if (auto *stinkCard = dynamic_cast<Stink *>(playedCard.get()))
                    {
                        currentPlayer.addCardToChain<Stink>(std::move(playedCard));
                    }
                    else if (auto *blueCard = dynamic_cast<Blue *>(playedCard.get()))
                    {
                        currentPlayer.addCardToChain<Blue>(std::move(playedCard));
                    }
                    else if (auto *chiliCard = dynamic_cast<Chili *>(playedCard.get()))
                    {
                        currentPlayer.addCardToChain<Chili>(std::move(playedCard));
                    }
                    else if (auto *greenCard = dynamic_cast<Green *>(playedCard.get()))
                    {
                        currentPlayer.addCardToChain<Green>(std::move(playedCard));
                    }
                    else if (auto *soyCard = dynamic_cast<Soy *>(playedCard.get()))
                    {
                        currentPlayer.addCardToChain<Soy>(std::move(playedCard));
                    }
                    else if (auto *blackCard = dynamic_cast<Black *>(playedCard.get()))
                    {
                        currentPlayer.addCardToChain<Black>(std::move(playedCard));
                    }
                    else if (auto *redCard = dynamic_cast<Red *>(playedCard.get()))
                    {
                        currentPlayer.addCardToChain<Red>(std::move(playedCard));
                    }
                    else if (auto *gardenCard = dynamic_cast<Garden *>(playedCard.get()))
                    {
                        currentPlayer.addCardToChain<Garden>(std::move(playedCard));
                    }
                    else
                    {
                        throw std::runtime_error("Unknown card type");
                    }
                    std::cout << "Card chained.\n";
                }
                catch (const std::exception &e)
                {
                    currentPlayer.addToFrontOfHand(std::move(playedCard)); // Need to implement this
                    // std::cout << "Failed to create chain: " << e.what() << "\n";
                }
            }
            catch (const std::exception &e)
            {
                std::cout << "Error: " << e.what() << "\n";
            }
        }

        if (getUserChoice("\nWould you like to harvest any chains?"))
        {
            std::cout << "Available chains to harvest:\n";
            for (int i = 0; i < currentPlayer.getNumChains(); i++)
            {
                try
                {
                    auto &chain = currentPlayer[i];
                    if (chain.size() > 0)
                    {
                        std::cout << i + 1 << ". ";
                        chain.print(std::cout);
                        std::cout << " (Value: " << chain.sell() << " coins)\n";
                    }
                }
                catch (const std::exception &e)
                {
                    continue;
                }
            }

            std::cout << "Enter chain number to harvest (1-" << currentPlayer.getNumChains()
                      << ") or 0 to cancel: ";
            int chainNum;
            std::cin >> chainNum;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (chainNum > 0 && chainNum <= currentPlayer.getNumChains())
            {
                try
                {
                    auto &chain = currentPlayer[chainNum - 1];
                    std::string chainType = chain.getType();
                    int coins = 0;

                    if (chainType == "Blue")
                        coins = currentPlayer.harvestChain<Blue>();
                    else if (chainType == "Chili")
                        coins = currentPlayer.harvestChain<Chili>();
                    else if (chainType == "Stink")
                        coins = currentPlayer.harvestChain<Stink>();
                    else if (chainType == "Green")
                        coins = currentPlayer.harvestChain<Green>();
                    else if (chainType == "Soy")
                        coins = currentPlayer.harvestChain<Soy>();
                    else if (chainType == "Black")
                        coins = currentPlayer.harvestChain<Black>();
                    else if (chainType == "Red")
                        coins = currentPlayer.harvestChain<Red>();
                    else if (chainType == "Garden")
                        coins = currentPlayer.harvestChain<Garden>();

                    if (coins > 0)
                    {
                        std::cout << "Harvested " << coins << " coins!\n";
                    }
                }
                catch (const std::exception &e)
                {
                    std::cout << "Error harvesting chain: " << e.what() << "\n";
                }
            }
        }
        // Discard phase
        if (getUserChoice("\nWould you like to discard a card?"))
        {
            currentPlayer.printHand(std::cout, true);
            std::cout << "Enter index of card to discard: ";
            int index;
            std::cin >> index;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            try
            {
                auto discardedCard = currentPlayer.getCardFromHand(index);
                gameTable->getDiscardPile() += std::move(discardedCard);
                std::cout << gameTable->getDiscardPile();
                std::cout
                    << "Card discarded.\n";
            }
            catch (const std::exception &e)
            {
                std::cout << "Error discarding card: " << e.what() << "\n";
            }
        }

        // Draw trade cards
        std::cout << ">>> " << currentPlayer.getName() << " draws three cards from deck and places in trade area." << std::endl
                  << std::endl;

        for (int i = 0; i < 3 && !gameTable->getDeck().empty(); ++i)
        {
            gameTable->getTradeArea() += std::move(gameTable->getDeck().draw());
        }
        std::cout << gameTable->getTradeArea();

        // Process matching cards from discard pile
        while (!gameTable->getDiscardPile().empty() &&
               gameTable->getTradeArea().legal(gameTable->getDiscardPile().top()))
        {
            gameTable->getTradeArea() += std::move(gameTable->getDiscardPile().pickUp());
        }

        // Draw end phase cards
        for (int i = 0; i < 2 && !gameTable->getDeck().empty(); ++i)
        {
            currentPlayer.addToHand(std::move(gameTable->getDeck().draw()));
        }

        gameTable->nextPlayer();

        std::cout << "\nPress Enter to continue...";
        std::cin.get();
    }

    // Game end
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