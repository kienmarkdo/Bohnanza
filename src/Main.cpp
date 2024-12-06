#include <iostream>
#include <stdexcept>
#include <string>
#include "Card.h"
#include "CardFactory.h"
#include "Table.h"
#include "Player.h"
#include "Chain.h"
#include "DiscardPile.h"
#include "TradeArea.h"
#include "Hand.h"
#include "Deck.h"

static void printCommands() {
    std::cout << "Commands:\n"
              << "  show            - Show the current game state\n"
              << "  play            - Play the top card from your hand onto a chain if possible, else discard\n"
              << "  trade           - Attempt to place top card of your hand into the TradeArea if legal, else discard\n"
              << "  discard         - Discard the top card of your hand\n"
              << "  end             - End your turn\n"
              << std::endl;
}

int main() {
    try {
        CardFactory* factory = CardFactory::getFactory();
        Deck deck = factory->getDeck();

        Table table("Alice", "Bob", std::move(deck));
        Player& p1 = table.getPlayer1();
        Player& p2 = table.getPlayer2();

        // Deal initial hands (5 cards each for example)
        for (int i = 0; i < 5; ++i) {
            p1 += table.getDeck().draw();
            p2 += table.getDeck().draw();
        }

        // Create initial chains (example)
        p1.createChain<Blue>();
        p1.createChain<Chili>();
        p2.createChain<Stink>();
        p2.createChain<Green>();

        std::cout << "Welcome to the Interactive Card Game!\n";
        std::cout << "There are two players: " << p1.getName() << " and " << p2.getName() << "." << std::endl;

        bool gameOver = false;
        Player* currentPlayer = &p1;
        Player* otherPlayer = &p2;
        int turnCount = 1;

        while (!gameOver) {
            // Check if deck is empty -> game over
            if (table.getDeck().size() == 0) {
                gameOver = true;
                break;
            }

            std::cout << "\n=== Turn " << turnCount << " ===" << std::endl;
            std::cout << "Current player: " << currentPlayer->getName() << std::endl;

            // Draw a card at the start of turn if available
            if (table.getDeck().size() > 0) {
                Card* drawn = table.getDeck().draw();
                if (drawn) {
                    *currentPlayer += drawn;
                    std::cout << currentPlayer->getName() << " draws a card." << std::endl;
                }
            }

            bool endTurn = false;
            printCommands();

            while (!endTurn && !gameOver) {
                std::cout << currentPlayer->getName() << ", enter command: ";
                std::string command;
                std::cin >> command;

                if (command == "show") {
                    std::cout << table << std::endl;
                    std::cout << currentPlayer->getName() << "'s hand: " << std::endl;
                    std::cout << *currentPlayer->topCard() << " (top card)" << std::endl;
                    // Note: We only print top card. If you want the full hand, modify Hand to allow printing safely.
                } else if (command == "play") {
                    Card* top = currentPlayer->topCard();
                    if (!top) {
                        std::cout << "Your hand is empty!" << std::endl;
                        continue;
                    }
                    // Try to play top card onto a matching chain
                    Card* card = currentPlayer->playCard();
                    if (!card) {
                        std::cout << "No card to play." << std::endl;
                        continue;
                    }

                    std::string name = card->getName();
                    bool played = false;
                    // Try to find a chain that matches the card's bean type
                    for (int i = 0; i < currentPlayer->getNumChains(); ++i) {
                        if (currentPlayer->operator[](i).getBeanName() == name) {
                            currentPlayer->operator[](i) += card;
                            std::cout << "Played " << name << " card on chain " << (i+1) << std::endl;
                            played = true;
                            break;
                        }
                    }

                    if (!played) {
                        // If no suitable chain, discard it
                        table.getDiscardPile() += card;
                        std::cout << "No suitable chain for " << name << ", card discarded." << std::endl;
                    }
                } else if (command == "trade") {
                    // Attempt to put the top card of the player's hand into the TradeArea if legal
                    Card* top = currentPlayer->topCard();
                    if (!top) {
                        std::cout << "Your hand is empty!" << std::endl;
                        continue;
                    }
                    Card* card = currentPlayer->playCard(); // remove from hand
                    if (!card) {
                        std::cout << "No card to trade." << std::endl;
                        continue;
                    }
                    if (table.getTradeArea().legal(card)) {
                        table.getTradeArea() += card;
                        std::cout << "Added " << card->getName() << " to the TradeArea." << std::endl;
                    } else {
                        // discard if not legal
                        table.getDiscardPile() += card;
                        std::cout << "Not legal to add " << card->getName() << " to TradeArea, card discarded." << std::endl;
                    }
                } else if (command == "discard") {
                    Card* top = currentPlayer->topCard();
                    if (!top) {
                        std::cout << "Your hand is empty!" << std::endl;
                        continue;
                    }
                    Card* card = currentPlayer->playCard();
                    table.getDiscardPile() += card;
                    std::cout << "Discarded " << card->getName() << std::endl;
                } else if (command == "end") {
                    // End this player's turn
                    endTurn = true;
                } else {
                    std::cout << "Unknown command." << std::endl;
                    printCommands();
                }

                // Check if deck is empty after actions
                if (table.getDeck().size() == 0) {
                    gameOver = true;
                }
            }

            // Switch player
            Player* temp = currentPlayer;
            currentPlayer = otherPlayer;
            otherPlayer = temp;
            turnCount++;
        }

        // Game ended
        std::cout << "\nGame Over! The deck is empty." << std::endl;
        std::cout << "Final state:\n" << table << std::endl;
        std::cout << p1.getName() << " has " << p1.getNumCoins() << " coins." << std::endl;
        std::cout << p2.getName() << " has " << p2.getNumCoins() << " coins." << std::endl;

        if (p1.getNumCoins() > p2.getNumCoins()) {
            std::cout << p1.getName() << " wins!" << std::endl;
        } else if (p2.getNumCoins() > p1.getNumCoins()) {
            std::cout << p2.getName() << " wins!" << std::endl;
        } else {
            std::cout << "It's a tie!" << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "Exception occurred: " << e.what() << std::endl;
    }

    return 0;
}
