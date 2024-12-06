#ifndef CARD_FACTORY_H
#define CARD_FACTORY_H

#include <vector>
#include <memory>
#include <map>
#include "Card.h"
#include "Deck.h"

/**
 * @brief The CardFactory is a singleton class responsible for creating and managing all
 *        card instances. It initializes card pools, can shuffle them into a deck, and create
 *        individual cards by name for loading saved games.
 */
class CardFactory {
public:
    // Disable copy and assignment to preserve singleton nature
    CardFactory(const CardFactory &) = delete;
    CardFactory &operator=(const CardFactory &) = delete;

    /**
     * @brief Get the singleton instance of the CardFactory.
     * @return A shared_ptr to the CardFactory instance.
     */
    static std::shared_ptr<CardFactory> getFactory();

    /**
     * @brief Create and return a deck populated with all the game's cards in a random order.
     * @return A unique_ptr to a newly created and shuffled Deck.
     */
    std::unique_ptr<Deck> getDeck();

    /**
     * @brief Create a single card by its name. Used when loading a saved game.
     * @param cardName The name of the card to create (e.g. "Blue", "Chili").
     * @return A unique_ptr to the newly created Card.
     * @throws std::runtime_error if the card name is invalid.
     */
    std::unique_ptr<Card> createCard(const std::string &cardName);

    /**
     * @brief Cleanup the CardFactory instance. Resets the singleton.
     */
    static void cleanup() {
        std::cout << "Starting CardFactory cleanup...\n";
        instance.reset();
        std::cout << "CardFactory cleanup complete\n";
    }

    ~CardFactory() {
        try {
            cards.clear();
        }
        catch (const std::exception &e) {
            std::cerr << "Error in CardFactory destructor: " << e.what() << "\n";
        }
        std::cout << "CardFactory destructor end\n";
    }

private:
    // Private constructor for the singleton
    CardFactory();

    // Singleton instance
    static std::shared_ptr<CardFactory> instance;

    // Map from card name to a vector of unique_ptr<Card> representing the card pool
    std::map<std::string, std::vector<std::unique_ptr<Card>>> cards;

    /**
     * @brief Initialize the card pools with the correct number of each bean type.
     */
    void initializeCards();
};

#endif // CARD_FACTORY_H
