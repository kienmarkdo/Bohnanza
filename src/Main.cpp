#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <limits>
#include "Card.h"
#include "CardFactory.h"
#include "Table.h"
#include "Player.h"
#include "Chain.h"
#include "DiscardPile.h"
#include "TradeArea.h"
#include "Hand.h"
#include "Deck.h"

// Simple comments only.

static void printCommands() {
    std::cout << "Commands:\n"
              << "  show       - Show state\n"
              << "  play       - Play top card\n"
              << "  trade      - Trade top card if legal\n"
              << "  discard    - Discard top card\n"
              << "  buychain   - Buy third chain\n"
              << "  sell       - Sell a chain\n"
              << "  save       - Save game\n"
              << "  end        - End turn\n\n";
}

static void displayState(const Table& table, const Player& player) {
    std::cout << "\n" << table << "\n";
    std::cout << player.getName() << "'s hand: " << player.getHand() << "\n\n";
}

static void pressEnterToContinue() {
    std::cout << "Press Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (std::cin.peek() == '\n') {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cout << "=================================================================" << std::endl;
}

static void createChainForCard(Player& player, Card* card) {
    if (dynamic_cast<Blue*>(card)) player.createChain<Blue>();
    else if (dynamic_cast<Chili*>(card)) player.createChain<Chili>();
    else if (dynamic_cast<Stink*>(card)) player.createChain<Stink>();
    else if (dynamic_cast<Green*>(card)) player.createChain<Green>();
    else if (dynamic_cast<Soy*>(card)) player.createChain<Soy>();
    else if (dynamic_cast<Black*>(card)) player.createChain<Black>();
    else if (dynamic_cast<Red*>(card)) player.createChain<Red>();
    else if (dynamic_cast<Garden*>(card)) player.createChain<Garden>();
    else throw std::runtime_error("Unknown card type");
}

static void sellChain(Player& player, Table& table) {
    if (player.getNumChains() == 0) {
        std::cout << "No chains.\n\n";
        return;
    }
    std::cout << "Which chain (1-" << player.getNumChains() << ")? ";
    int index;
    std::cin >> index;
    index -= 1;
    if (index < 0 || index >= player.getNumChains()) {
        std::cout << "Invalid.\n\n";
        return;
    }
    int coins = player[index].sell();
    if (coins == 0) {
        std::cout << "No coins.\n\n";
        return;
    }
    Card* ex = player[index].frontCard();
    int needed = ex->getCardsPerCoin(coins);
    player[index].removeFrontCards(needed, table.getDiscardPile());
    player.addCoins(coins);
    std::cout << player.getName() << " sold " << needed << " card(s) for " << coins << " coin(s).\n\n";
}

static void playTopCard(Player& player, Table& table) {
    Card* top = player.topCard();
    if (!top) {
        std::cout << player.getName() << "'s hand is empty.\n\n";
        return;
    }
    Card* card = player.playCard();
    if (!card) {
        std::cout << "No card available.\n\n";
        return;
    }
    std::string name = card->getName();
    bool played = false;
    for (int i = 0; i < player.getNumChains(); ++i) {
        if (player[i].getBeanName() == name) {
            player[i] += card;
            std::cout << player.getName() << " placed a " << name << " card.\n\n";
            played = true;
            break;
        }
    }
    if (!played) {
        if (player.getNumChains() < player.getMaxNumChains()) {
            createChainForCard(player, card);
            player[player.getNumChains()-1] += card;
            std::cout << player.getName() << " started a new " << name << " chain.\n\n";
        } else {
            table.getDiscardPile() += card;
            std::cout << "No chain slot. Card discarded.\n\n";
        }
    }
}

static void attemptBuyThirdChain(Player& player) {
    if (player.getMaxNumChains() >= 3) {
        std::cout << player.getName() << " has max chains.\n\n";
        return;
    }
    try {
        bool success = player.buyThirdChain();
        if (success) std::cout << player.getName() << " bought a third chain.\n\n";
        else std::cout << player.getName() << " not enough coins.\n\n";
    } catch (const std::exception& e) {
        std::cout << "Cannot buy chain: " << e.what() << "\n\n";
    }
}

static void saveGame(const Table& table) {
    std::ofstream out("savefile.txt");
    if (!out) {
        std::cout << "Error saving.\n";
        return;
    }
    out << table;
    out.close();
    std::cout << "Game saved.\n";
}

static Table loadGame(CardFactory* factory) {
    std::ifstream in("savefile.txt");
    if (!in) {
        std::cout << "No save file.\n";
        return Table("DefaultP1", "DefaultP2", factory->getDeck());
    }
    Table t(in, factory);
    return t;
}

int main() {
    try {
        CardFactory* factory = CardFactory::getFactory();
        std::cout << "Load previous game (y/n)? ";
        char choice; std::cin >> choice;
        Table table("", "", Deck());
        Player *p1, *p2;

        if (choice == 'y') {
            table = loadGame(factory);
            p1 = &table.getPlayer1();
            p2 = &table.getPlayer2();
        } else {
            std::string p1Name, p2Name;
            std::cout << "Enter name for Player 1: ";
            std::cin >> p1Name;
            std::cout << "Enter name for Player 2: ";
            std::cin >> p2Name;
            Deck deck = factory->getDeck();
            table = Table(p1Name, p2Name, std::move(deck));
            p1 = &table.getPlayer1();
            p2 = &table.getPlayer2();
            for (int i = 0; i < 5; ++i) {
                *p1 += table.getDeck().draw();
                *p2 += table.getDeck().draw();
            }
        }

        std::cout << "\nWelcome!\nPlayers: " << p1->getName() << " and " << p2->getName() << ".\n";

        bool gameOver = false;
        Player* currentPlayer = p1;
        Player* otherPlayer = p2;
        int turnCount = 1;

        while (!gameOver) {
            if (table.getDeck().size() == 0) {
                gameOver = true;
                break;
            }

            std::cout << "\n=== Turn " << turnCount << " ===\n" << currentPlayer->getName() << "'s turn.\n\n";
            if (table.getDeck().size() > 0) {
                Card* drawn = table.getDeck().draw();
                if (drawn) {
                    *currentPlayer += drawn;
                    std::cout << currentPlayer->getName() << " draws a card.\n\n";
                }
            }

            printCommands();
            displayState(table, *currentPlayer);

            bool endTurn = false;
            while (!endTurn && !gameOver) {
                std::cout << currentPlayer->getName() << ", enter command: ";
                std::string command;
                std::cin >> command;

                bool actionTaken = false;

                if (command == "show") {
                    displayState(table, *currentPlayer);
                } else if (command == "play") {
                    playTopCard(*currentPlayer, table);
                    pressEnterToContinue();
                    actionTaken = true;
                } else if (command == "trade") {
                    Card* top = currentPlayer->topCard();
                    if (!top) std::cout << currentPlayer->getName() << "'s hand empty.\n\n";
                    else {
                        Card* card = currentPlayer->playCard();
                        if (!card) std::cout << "No card.\n\n";
                        else {
                            if (table.getTradeArea().legal(card)) {
                                table.getTradeArea() += card;
                                std::cout << currentPlayer->getName() << " traded " << card->getName() << ".\n\n";
                            } else {
                                table.getDiscardPile() += card;
                                std::cout << "Not legal. Card discarded.\n\n";
                            }
                        }
                    }
                    pressEnterToContinue();
                    actionTaken = true;
                } else if (command == "discard") {
                    Card* top = currentPlayer->topCard();
                    if (!top) std::cout << currentPlayer->getName() << "'s hand empty.\n\n";
                    else {
                        Card* card = currentPlayer->playCard();
                        table.getDiscardPile() += card;
                        std::cout << currentPlayer->getName() << " discarded " << card->getName() << ".\n\n";
                    }
                    pressEnterToContinue();
                    actionTaken = true;
                } else if (command == "buychain") {
                    attemptBuyThirdChain(*currentPlayer);
                    pressEnterToContinue();
                    actionTaken = true;
                } else if (command == "sell") {
                    sellChain(*currentPlayer, table);
                    pressEnterToContinue();
                    actionTaken = true;
                } else if (command == "save") {
                    saveGame(table);
                    std::cout << "Quit after saving (y/n)? ";
                    char q; std::cin >> q;
                    if (q == 'y') return 0;
                } else if (command == "end") {
                    endTurn = true;
                    std::cout << "Ending " << currentPlayer->getName() << "'s turn.\n\n";
                    pressEnterToContinue();
                    actionTaken = true;
                } else {
                    std::cout << "Unknown command.\n\n";
                    printCommands();
                }

                if (table.getDeck().size() == 0) {
                    gameOver = true;
                }

                if (actionTaken && !gameOver && !endTurn) {
                    displayState(table, *currentPlayer);
                }
            }

            Player* temp = currentPlayer;
            currentPlayer = otherPlayer;
            otherPlayer = temp;
            turnCount++;
        }

        std::cout << "\nGame Over!\n" << table << "\n";
        std::cout << p1->getName() << " has " << p1->getNumCoins() << " coins.\n";
        std::cout << p2->getName() << " has " << p2->getNumCoins() << " coins.\n";
        if (p1->getNumCoins() > p2->getNumCoins()) std::cout << p1->getName() << " wins!\n";
        else if (p2->getNumCoins() > p1->getNumCoins()) std::cout << p2->getName() << " wins!\n";
        else std::cout << "It's a tie!\n";

    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
