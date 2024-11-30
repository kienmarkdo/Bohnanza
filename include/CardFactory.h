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

    // Singleton access method - returns shared_ptr instead of raw pointer
    static std::shared_ptr<CardFactory> getFactory();

    // Get a new deck with all cards
    std::unique_ptr<Deck> getDeck();

    // Helper methods to create specific cards (used for loading games)
    std::unique_ptr<Card> createCard(const std::string &cardName);

    // Cleanup method
    static void cleanup()
    {
        std::cout << "Starting CardFactory cleanup...\n";
        instance.reset();
        std::cout << "CardFactory cleanup complete\n";
    }

    ~CardFactory()
    {
        try
        {
            cards.clear();
                }
        catch (const std::exception &e)
        {
            std::cerr << "Error in CardFactory destructor: " << e.what() << "\n";
        }
        std::cout << "CardFactory destructor end\n";
    }

private:
    // Private constructor for singleton
    CardFactory();

    // Singleton instance
    static std::shared_ptr<CardFactory> instance;

    // Single container for all cards
    std::map<std::string, std::vector<std::unique_ptr<Card>>> cards;

    // Helper method to initialize card pools
    void initializeCards();
};

#endif // CARD_FACTORY_H