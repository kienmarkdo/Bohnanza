#ifndef CARDFACTORY_H
#define CARDFACTORY_H

#include <vector>
#include <algorithm>
#include <random>
#include "Card.h"
using namespace std;

/**
 * Singleton class for managing card creation and providing a shuffled deck.
 * The card factory serves as a factory for all the beans cards.
 */
class CardFactory {
public:
    /**
     * Returns the single instance of the CardFactory.
     * @return A pointer to the CardFactory instance.
     */
    static CardFactory* getFactory();

    /**
     * Generates a complete deck of 104 cards (as per game rules) and shuffles it.
     * @return A shuffled vector of Card pointers.
     */
    vector<Card*> getDeck();

    /**
     * Destructor to clean up dynamically allocated cards.
     */
    ~CardFactory();

private:
    /**
     * Private constructor to enforce singleton pattern.
     */
    CardFactory();

    /// Static instance of the CardFactory.
    static CardFactory* instance;

    /// Helper function to initialize the deck with specific counts of each card type.
    void initializeDeck();

    /// The deck of cards managed by the factory.
    vector<Card*> deck;
};

#endif
