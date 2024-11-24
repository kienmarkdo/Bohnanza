#ifndef CARD_FACTORY_H
#define CARD_FACTORY_H

#include <vector>
#include <memory>
#include <map>
#include "Card.h"
#include "Deck.h"

class CardFactory
{
public:
    // Delete copy and assignment operations
    CardFactory(const CardFactory &) = delete;
    CardFactory &operator=(const CardFactory &) = delete;

    // Singleton access method
    static CardFactory *getFactory();

    // Get a new deck with all cards
    Deck getDeck();

    ~CardFactory()
    {
        std::cout << "CardFactory destructor start\n";
        try
        {
            // Clear all cards
            cards.clear();
            std::cout << "All cards cleared\n";
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error in CardFactory destructor: " << e.what() << "\n";
        }
        std::cout << "CardFactory destructor end\n";
    }

    // Helper methods to create specific cards (used for loading games)
    Card *createCard(const std::string &cardName);
    static void cleanup()
    {
        std::cout << "Starting CardFactory cleanup...\n";
        instance.reset();
        std::cout << "CardFactory cleanup complete\n";
    }

private:
    // Private constructor for singleton
    CardFactory();

    // Singleton instance
    static std::unique_ptr<CardFactory> instance;

    // Single container for all cards
    std::map<std::string, std::vector<std::unique_ptr<Card>>> cards;

    // Helper method to initialize card pools
    void initializeCards();

    // Helper method to get all cards for deck creation
    std::vector<Card *> getAllCards() const;
};

#endif // CARD_FACTORY_H