#include <iostream>
#include <fstream>
#include "Table.h"
#include "CardFactory.h"

using namespace std;

// Function to save the current game state
void saveGame(const Table& table, const string& filename) {
    ofstream outFile(filename);
    if (outFile.is_open()) {
        outFile << table;
        outFile.close();
        cout << "Game saved successfully!" << endl;
    } else {
        cout << "Failed to save the game." << endl;
    }
}

// Function to load a saved game
bool loadGame(Table& table, const string& filename) {
    ifstream inFile(filename);
    if (inFile.is_open()) {
        inFile >> table;
        inFile.close();
        cout << "Game loaded successfully!" << endl;
        return true;
    } else {
        cout << "No saved game found." << endl;
        return false;
    }
}

int main() {
    // Setup players
    string player1Name, player2Name;
    cout << "Enter Player 1 Name: ";
    cin >> player1Name;
    cout << "Enter Player 2 Name: ";
    cin >> player2Name;

    Player player1(player1Name);
    Player player2(player2Name);

    // Setup table with players and deck from the CardFactory
    CardFactory* factory = CardFactory::getFactory();
    Table table(player1, player2);

    // Load previous game if available
    string saveFile = "game_save.txt";
    char choice;
    cout << "Do you want to load the previous game? (y/n): ";
    cin >> choice;
    if (choice == 'y' || choice == 'Y') {
        if (!loadGame(table, saveFile)) {
            cout << "Starting a new game..." << endl;
        }
    } else {
        // Deal initial cards to players (5 cards each)
        for (int i = 0; i < 5; ++i) {
            player1.drawCard(table.getDeck().draw());
            player2.drawCard(table.getDeck().draw());
        }
    }

    bool gameRunning = true;

    while (gameRunning) {
        // Alternate between player turns
        for (int turn = 0; gameRunning; ++turn) {
            Player& currentPlayer = (turn % 2 == 0) ? player1 : player2;

            cout << "\n" << currentPlayer.getName() << "'s turn:" << endl;

            // If trade area is not empty, add cards to chains or discard them
            if (!table.getTradeArea().isEmpty()) {
                cout << "There are cards in the trade area. You must add them to your chains or discard them." << endl;
                // Logic to add cards from trade area to chains or discard them
                for (Card* card : table.getTradeArea().getCards()) {
                    cout << "Trade Area Card: " << card->getName() << "\nOptions:\n1. Add to existing chain\n2. Discard" << endl;
                    int action;
                    cin >> action;
                    if (action == 1) {
                        bool added = false;
                        for (int i = 0; i < currentPlayer.getNumChains(); ++i) {
                            try {
                                currentPlayer[i] += card;
                                added = true;
                                break;
                            } catch (const IllegalType&) {
                                // Card type doesn't match, move to next chain
                            }
                        }
                        if (!added) {
                            cout << "No matching chain found. Discarding the card." << endl;
                            table.getDiscardPile().push(card);
                        }
                    } else {
                        table.getDiscardPile().push(card);
                    }
                }
                table.getTradeArea().clear();
            }

            // Play topmost card from hand
            Card* topCard = currentPlayer.playTopCard();
            if (topCard) {
                cout << "Playing the top card from hand: " << topCard->getName() << endl;

                // Attempt to add the card to an existing chain or create a new chain
                bool added = false;
                for (int i = 0; i < currentPlayer.getNumChains(); ++i) {
                    try {
                        currentPlayer[i] += topCard;
                        added = true;
                        break;
                    } catch (const IllegalType&) {
                        // Card type doesn't match, move to next chain
                    }
                }

                if (!added) {
                    // No matching chain, so the player must sell an existing chain if necessary
                    if (currentPlayer.getNumChains() >= currentPlayer.getMaxNumChains()) {
                        cout << "You need to sell an existing chain to start a new one." << endl;
                        // Logic to sell an existing chain and start a new one with the current card
                        int chainIndex;
                        cout << "Enter the chain index to sell: ";
                        cin >> chainIndex;
                        int coinsEarned = currentPlayer.sellChain(chainIndex);
                        currentPlayer.addCoins(coinsEarned);
                        cout << "Sold chain for " << coinsEarned << " coins." << endl;
                    }
                    // Start a new chain
                    currentPlayer.addChain(Chain<Card*>(topCard));
                    cout << "Started a new chain with " << topCard->getName() << endl;
                }
            }

            // Draw three cards from the deck and place them in the trade area
            cout << "Drawing three cards for the trade area..." << endl;
            for (int i = 0; i < 3; ++i) {
                Card* drawnCard = table.getDeck().draw();
                if (drawnCard) {
                    table.addCardToTradeArea(drawnCard);
                }
            }

            // Draw two cards from deck and add them to player's hand
            cout << "Drawing two cards to add to your hand." << endl;
            for (int i = 0; i < 2; ++i) {
                Card* drawnCard = table.getDeck().draw();
                if (drawnCard) {
                    currentPlayer.drawCard(drawnCard);
                }
            }

            // Display the current state of the table
            cout << "\nCurrent Table State:" << endl;
            table.print(cout);

            // Check if the current player has won
            if (table.win(currentPlayer)) {
                cout << currentPlayer.getName() << " has won the game!" << endl;
                gameRunning = false;
                break;
            }

            // Ask to save and exit
            cout << "Do you want to save the game and exit? (y/n): ";
            cin >> choice;
            if (choice == 'y' || choice == 'Y') {
                saveGame(table, saveFile);
                gameRunning = false;
                break;
            }
        }
    }

    cout << "Thanks for playing!" << endl;
    return 0;
}
