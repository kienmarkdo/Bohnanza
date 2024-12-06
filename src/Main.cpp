#include <fstream>
#include <iostream>
#include <string>
#include <limits>
#include <stdexcept>
#include <memory>
#include "CardFactory.h"
#include "Table.h"

/**
 * @brief Utility function to get a yes/no input from the user.
 * @param prompt The question to ask the user.
 * @return True if user enters 'y', false if user enters 'n'.
 */
bool getUserChoice(const std::string &prompt) {
    std::string input;
    while (true) {
        std::cout << prompt << " (y/n): ";

        if (!std::getline(std::cin, input)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        input.erase(0, input.find_first_not_of(" \t\n\r\f\v"));
        input.erase(input.find_last_not_of(" \t\n\r\f\v") + 1);

        if (input.length() == 1) {
            char choice = std::tolower(input[0]);
            if (choice == 'y') return true;
            if (choice == 'n') return false;
        }

        std::cout << "Invalid input. Please enter 'y' or 'n'.\n";
    }
}

/**
 * @brief Clears the console screen. Implementation depends on the platform.
 */
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

/**
 * @brief The main function starts the Bean Trading Card Game.
 *        Allows the user to start a new game or load a saved game, then runs the game loop.
 * @return Exit status code.
 */
int main() {
    std::cout << "=== Bean Trading Card Game ===\n\n";

    std::cout << "Creating CardFactory...\n";
    auto factory = CardFactory::getFactory();

    // Prompt user to load a saved game or start fresh
    bool loadGame = getUserChoice("Would you like to load a saved game?");
    std::unique_ptr<Table> gameTable;

    if (loadGame) {
        // Loading saved game
        std::string filename;
        std::cout << "Enter the filename to load from: ";
        std::getline(std::cin, filename);
        std::ifstream loadFile(filename);
        if (!loadFile) {
            std::cerr << "Error: Could not open file for loading: " << filename << "\n";
            return 1;
        }
        try {
            gameTable = std::make_unique<Table>(loadFile, factory.get());
            std::cout << "Game loaded successfully!\n";
        } catch (const std::exception &e) {
            std::cerr << "Error loading game: " << e.what() << "\n";
            return 1;
        }
    } else {
        // Starting a new game
        std::string player1, player2;
        std::cout << "Enter name for Player 1: ";
        std::getline(std::cin, player1);
        std::cout << "Enter name for Player 2: ";
        std::getline(std::cin, player2);

        std::cout << "Creating game table...\n";
        gameTable = std::make_unique<Table>(player1, player2);

        std::cout << "Creating initial deck...\n";
        auto initialDeck = factory->getDeck();
        std::cout << "Initial deck size: " << initialDeck->size() << "\n";

        // Set the deck
        gameTable->getDeck() = std::move(*initialDeck);

        // Deal initial hands to each player
        std::cout << "Dealing initial hands...\n";
        for (int i = 0; i < 5; ++i) {
            if (gameTable->getDeck().empty()) {
                std::cout << "Error: Deck empty while dealing initial hands\n";
                break;
            }

            auto card1 = gameTable->getDeck().draw();
            auto card2 = gameTable->getDeck().draw();

            if (card1 && card2) {
                gameTable->getPlayer(1).addToHand(std::move(card1));
                gameTable->getPlayer(2).addToHand(std::move(card2));
            } else {
                std::cout << "Error: Null card drawn\n";
                break;
            }
        }
    }

    // Main game loop runs until the deck is empty or the game is ended
    while (gameTable && !gameTable->getDeck().empty()) {
        std::cout << *gameTable;

        Player &currentPlayer = gameTable->getPlayer(gameTable->getCurrentPlayer());
        std::cout << "\n=== " << currentPlayer.getName() << "'s Turn ===\n";

        // Option to save the game mid-play
        if (getUserChoice("Would you like to pause and save the game?")) {
            std::string filename;
            std::cout << "Enter filename to save: ";
            std::getline(std::cin, filename);

            try {
                std::ofstream saveFile(filename);
                if (!saveFile) {
                    throw std::runtime_error("Could not open file for saving: " + filename);
                }
                gameTable->saveGame(saveFile);
                std::cout << "Game saved successfully!\n";

                if (!getUserChoice("Would you like to continue playing?")) {
                    std::cout << "Starting cleanup...\n";
                    gameTable.reset();
                    std::cout << "Game table cleared\n";
                    return 0;
                }
            } catch (const std::exception &e) {
                std::cerr << "Error during save: " << e.what() << "\n";
                return 1;
            }
        }

        // Player draws a card
        if (!gameTable->getDeck().empty()) {
            auto drawnCard = gameTable->getDeck().draw();
            if (drawnCard) {
                std::cout << "\nDrawn card: " << drawnCard->getName() << "\n";
                currentPlayer.addToHand(std::move(drawnCard));
            }
        }

        // Option to buy a third chain if player can afford it
        if (currentPlayer.getNumCoins() >= 3 && currentPlayer.getMaxNumChains() == 2) {
            if (getUserChoice("Would you like to buy a third chain for 3 coins?")) {
                try {
                    currentPlayer.buyThirdChain();
                    std::cout << "Third chain purchased successfully!\n";
                } catch (const NotEnoughCoins &e) {
                    std::cout << "Error: Not enough coins to buy third chain.\n";
                } catch (const std::runtime_error &e) {
                    std::cout << "Error: " << e.what() << "\n";
                }
            }
        }

        // Trade area phase: player may add cards from the trade area to their chains
        if (!gameTable->getTradeArea().empty()) {
            std::cout << "\nCurrent trade area: " << gameTable->getTradeArea() << "\n";
            while (!gameTable->getTradeArea().empty() &&
                   getUserChoice("Would you like to add a card from the trade area to your chains?")) {
                std::cout << "Available beans in trade area: " << gameTable->getTradeArea() << "\n";
                std::cout << "Enter bean name to chain (or 'skip' to move on): ";
                std::string beanName;
                std::getline(std::cin, beanName);
                if (beanName == "skip") {
                    break;
                }
                try {
                    auto tradedCard = gameTable->getTradeArea().trade(beanName);

                    // Add the traded card to the appropriate chain based on its type
                    if (auto *stinkCard = dynamic_cast<Stink *>(tradedCard.get())) {
                        currentPlayer.addCardToChain<Stink>(std::move(tradedCard));
                    } else if (auto *blueCard = dynamic_cast<Blue *>(tradedCard.get())) {
                        currentPlayer.addCardToChain<Blue>(std::move(tradedCard));
                    } else if (auto *chiliCard = dynamic_cast<Chili *>(tradedCard.get())) {
                        currentPlayer.addCardToChain<Chili>(std::move(tradedCard));
                    } else if (auto *greenCard = dynamic_cast<Green *>(tradedCard.get())) {
                        currentPlayer.addCardToChain<Green>(std::move(tradedCard));
                    } else if (auto *soyCard = dynamic_cast<Soy *>(tradedCard.get())) {
                        currentPlayer.addCardToChain<Soy>(std::move(tradedCard));
                    } else if (auto *blackCard = dynamic_cast<Black *>(tradedCard.get())) {
                        currentPlayer.addCardToChain<Black>(std::move(tradedCard));
                    } else if (auto *redCard = dynamic_cast<Red *>(tradedCard.get())) {
                        currentPlayer.addCardToChain<Red>(std::move(tradedCard));
                    } else if (auto *gardenCard = dynamic_cast<Garden *>(tradedCard.get())) {
                        currentPlayer.addCardToChain<Garden>(std::move(tradedCard));
                    } else {
                        throw std::runtime_error("Unknown card type");
                    }

                    std::cout << "Card chained.\n";
                } catch (const std::exception &e) {
                    std::cout << "Error: " << e.what() << "\n";
                }
            }
        }

        // Play cards phase: player chooses a card from their hand to play
        try {
            auto playedCard = currentPlayer.playFromHand();
            std::cout << "\nPlayed card: " << playedCard->getName() << "\n";
            // Attempt to place played card into correct chain
            try {
                if (auto *stinkCard = dynamic_cast<Stink *>(playedCard.get())) {
                    currentPlayer.addCardToChain<Stink>(std::move(playedCard));
                } else if (auto *blueCard = dynamic_cast<Blue *>(playedCard.get())) {
                    currentPlayer.addCardToChain<Blue>(std::move(playedCard));
                } else if (auto *chiliCard = dynamic_cast<Chili *>(playedCard.get())) {
                    currentPlayer.addCardToChain<Chili>(std::move(playedCard));
                } else if (auto *greenCard = dynamic_cast<Green *>(playedCard.get())) {
                    currentPlayer.addCardToChain<Green>(std::move(playedCard));
                } else if (auto *soyCard = dynamic_cast<Soy *>(playedCard.get())) {
                    currentPlayer.addCardToChain<Soy>(std::move(playedCard));
                } else if (auto *blackCard = dynamic_cast<Black *>(playedCard.get())) {
                    currentPlayer.addCardToChain<Black>(std::move(playedCard));
                } else if (auto *redCard = dynamic_cast<Red *>(playedCard.get())) {
                    currentPlayer.addCardToChain<Red>(std::move(playedCard));
                } else if (auto *gardenCard = dynamic_cast<Garden *>(playedCard.get())) {
                    currentPlayer.addCardToChain<Garden>(std::move(playedCard));
                } else {
                    throw std::runtime_error("Unknown card type");
                }
                std::cout << "Card chained.\n";
            } catch (const std::exception &e) {
                // If adding to chain fails, put card back to front of hand
                currentPlayer.addToFrontOfHand(std::move(playedCard));
            }
        } catch (const std::exception &e) {
            std::cout << "Error: " << e.what() << "\n";
        }

        // Optional second card play
        if (getUserChoice("\nWould you like to play another card?")) {
            try {
                auto playedCard = currentPlayer.playFromHand();
                std::cout << "Played card: " << playedCard->getName() << "\n";
                // Attempt to place played card into correct chain
                try {
                    if (auto *stinkCard = dynamic_cast<Stink *>(playedCard.get())) {
                        currentPlayer.addCardToChain<Stink>(std::move(playedCard));
                    } else if (auto *blueCard = dynamic_cast<Blue *>(playedCard.get())) {
                        currentPlayer.addCardToChain<Blue>(std::move(playedCard));
                    } else if (auto *chiliCard = dynamic_cast<Chili *>(playedCard.get())) {
                        currentPlayer.addCardToChain<Chili>(std::move(playedCard));
                    } else if (auto *greenCard = dynamic_cast<Green *>(playedCard.get())) {
                        currentPlayer.addCardToChain<Green>(std::move(playedCard));
                    } else if (auto *soyCard = dynamic_cast<Soy *>(playedCard.get())) {
                        currentPlayer.addCardToChain<Soy>(std::move(playedCard));
                    } else if (auto *blackCard = dynamic_cast<Black *>(playedCard.get())) {
                        currentPlayer.addCardToChain<Black>(std::move(playedCard));
                    } else if (auto *redCard = dynamic_cast<Red *>(playedCard.get())) {
                        currentPlayer.addCardToChain<Red>(std::move(playedCard));
                    } else if (auto *gardenCard = dynamic_cast<Garden *>(playedCard.get())) {
                        currentPlayer.addCardToChain<Garden>(std::move(playedCard));
                    } else {
                        throw std::runtime_error("Unknown card type");
                    }
                    std::cout << "Card chained.\n";
                } catch (const std::exception &e) {
                    currentPlayer.addToFrontOfHand(std::move(playedCard));
                }
            } catch (const std::exception &e) {
                std::cout << "Error: " << e.what() << "\n";
            }
        }

        // Option to harvest chains for coins
        if (getUserChoice("\nWould you like to harvest any chains?")) {
            std::cout << "Available chains to harvest:\n";
            for (int i = 0; i < currentPlayer.getNumChains(); i++) {
                try {
                    auto &chain = currentPlayer[i];
                    if (chain.size() > 0) {
                        std::cout << i + 1 << ". ";
                        chain.print(std::cout);
                        std::cout << " (Value: " << chain.sell() << " coins)\n";
                    }
                } catch (const std::exception &e) {
                    continue;
                }
            }

            std::cout << "Enter chain number to harvest (1-" << currentPlayer.getNumChains()
                      << ") or 0 to cancel: ";
            int chainNum;
            std::cin >> chainNum;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (chainNum > 0 && chainNum <= currentPlayer.getNumChains()) {
                try {
                    auto &chain = currentPlayer[chainNum - 1];
                    std::string chainType = chain.getType();
                    int coins = 0;

                    // Harvest specific chain type
                    if (chainType == "Blue")   coins = currentPlayer.harvestChain<Blue>();
                    else if (chainType == "Chili")  coins = currentPlayer.harvestChain<Chili>();
                    else if (chainType == "Stink")  coins = currentPlayer.harvestChain<Stink>();
                    else if (chainType == "Green")  coins = currentPlayer.harvestChain<Green>();
                    else if (chainType == "Soy")    coins = currentPlayer.harvestChain<Soy>();
                    else if (chainType == "Black")  coins = currentPlayer.harvestChain<Black>();
                    else if (chainType == "Red")    coins = currentPlayer.harvestChain<Red>();
                    else if (chainType == "Garden") coins = currentPlayer.harvestChain<Garden>();

                    if (coins > 0) {
                        std::cout << "Harvested " << coins << " coins!\n";
                    }
                } catch (const std::exception &e) {
                    std::cout << "Error harvesting chain: " << e.what() << "\n";
                }
            }
        }

        // Discard phase: player may discard a card from hand
        if (getUserChoice("\nWould you like to discard a card?")) {
            currentPlayer.printHand(std::cout, true);
            std::cout << "Enter index of card to discard: ";
            int index;
            std::cin >> index;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            try {
                auto discardedCard = currentPlayer.getCardFromHand(index);
                gameTable->getDiscardPile() += std::move(discardedCard);
                std::cout << gameTable->getDiscardPile();
                std::cout << "Card discarded.\n";
            } catch (const std::exception &e) {
                std::cout << "Error discarding card: " << e.what() << "\n";
            }
        }

        // Draw three cards into trade area
        std::cout << ">>> " << currentPlayer.getName() << " draws three cards from deck and places in trade area.\n\n";
        for (int i = 0; i < 3 && !gameTable->getDeck().empty(); ++i) {
            gameTable->getTradeArea() += std::move(gameTable->getDeck().draw());
        }
        std::cout << gameTable->getTradeArea();

        // Move matching cards from discard pile to trade area if applicable
        while (!gameTable->getDiscardPile().empty() &&
               gameTable->getTradeArea().legal(gameTable->getDiscardPile().top())) {
            gameTable->getTradeArea() += std::move(gameTable->getDiscardPile().pickUp());
        }

        // End phase: draw two more cards for the player
        for (int i = 0; i < 2 && !gameTable->getDeck().empty(); ++i) {
            currentPlayer.addToHand(std::move(gameTable->getDeck().draw()));
        }

        // Move to the next player's turn
        gameTable->nextPlayer();

        std::cout << "\nPress Enter to continue...";
        std::cin.get();
    }

    // Game ends when deck is empty or after final actions
    std::string winnerName;
    if (gameTable && gameTable->win(winnerName)) {
        std::cout << "\nGame Over! The winner is: " << winnerName << "!\n";
    } else {
        std::cout << "\nGame Over! It's a tie!\n";
    }

    return 0;
}
