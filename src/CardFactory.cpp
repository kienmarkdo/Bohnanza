#include "CardFactory.h"

// Initialize the static instance to nullptr
CardFactory* CardFactory::instance = nullptr;

/**
 * Private constructor for CardFactory.
 * Initializes the deck with cards.
 */
CardFactory::CardFactory() {
    initializeDeck(); // Fill the deck with the required cards
}

/**
 * Destructor to clean up dynamically allocated cards.
 */
CardFactory::~CardFactory() {
    for (Card* card : deck) {
        delete card;
    }
}

/**
 * Returns the singleton instance of the CardFactory.
 * @return A pointer to the only CardFactory instance.
 */
CardFactory* CardFactory::getFactory() {
    if (instance == nullptr) {
        instance = new CardFactory();
    }
    return instance;
}

/**
 * Helper function to initialize the deck with specific counts of each card type.
 */
void CardFactory::initializeDeck() {
    // Add cards to the deck (based on game rules, each card type has a specific count)
    for (int i = 0; i < 20; ++i) deck.push_back(new Blue());     // 20 Blue cards
    for (int i = 0; i < 18; ++i) deck.push_back(new Chili());    // 18 Chili cards
    for (int i = 0; i < 16; ++i) deck.push_back(new Stink());    // 16 Stink cards
    for (int i = 0; i < 14; ++i) deck.push_back(new Green());    // 14 Green cards
    for (int i = 0; i < 12; ++i) deck.push_back(new soy());      // 12 soy cards
    for (int i = 0; i < 10; ++i) deck.push_back(new black());    // 10 black cards
    for (int i = 0; i < 8; ++i) deck.push_back(new Red());       // 8 Red cards
    for (int i = 0; i < 6; ++i) deck.push_back(new garden());    // 6 Garden cards

    // Shuffle the deck
    random_device rd;
    mt19937 g(rd());
    shuffle(deck.begin(), deck.end(), g);
}

/**
 * Generates and returns a shuffled deck of 104 bean cards.
 * @return A shuffled vector of Card pointers.
 */
vector<Card*> CardFactory::getDeck() {
    return deck; // Return the shuffled deck
}
