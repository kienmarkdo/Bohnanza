#include "CardFactory.h"
#include <algorithm>
#include <random>
#include <chrono>
#include <stdexcept>

std::unique_ptr<CardFactory> CardFactory::instance = nullptr;

// Add constructor implementation
CardFactory::CardFactory()
{
    initializeCards();
}

// Add getFactory implementation
CardFactory *CardFactory::getFactory()
{
    if (!instance)
    {
        instance = std::unique_ptr<CardFactory>(new CardFactory());
    }
    return instance.get();
}
void CardFactory::initializeCards()
{
    // Initialize all card pools according to the game requirements

    // Blue - 20 cards
    for (int i = 0; i < 20; ++i)
    {
        cards["Blue"].push_back(std::unique_ptr<Card>(BeanCreator<Blue>::create()));
    }

    // Chili - 18 cards
    for (int i = 0; i < 18; ++i)
    {
        cards["Chili"].push_back(std::unique_ptr<Card>(BeanCreator<Chili>::create()));
    }

    // Stink - 16 cards
    for (int i = 0; i < 16; ++i)
    {
        cards["Stink"].push_back(std::unique_ptr<Card>(BeanCreator<Stink>::create()));
    }

    // Green - 14 cards
    for (int i = 0; i < 14; ++i)
    {
        cards["Green"].push_back(std::unique_ptr<Card>(BeanCreator<Green>::create()));
    }

    // Soy - 12 cards
    for (int i = 0; i < 12; ++i)
    {
        cards["Soy"].push_back(std::unique_ptr<Card>(BeanCreator<Soy>::create()));
    }

    // Black - 10 cards
    for (int i = 0; i < 10; ++i)
    {
        cards["Black"].push_back(std::unique_ptr<Card>(BeanCreator<Black>::create()));
    }

    // Red - 8 cards
    for (int i = 0; i < 8; ++i)
    {
        cards["Red"].push_back(std::unique_ptr<Card>(BeanCreator<Red>::create()));
    }

    // Garden - 6 cards
    for (int i = 0; i < 6; ++i)
    {
        cards["Garden"].push_back(std::unique_ptr<Card>(BeanCreator<Garden>::create()));
    }
}

Deck CardFactory::getDeck()
{
    std::vector<Card *> allCards;
    allCards.reserve(104); // Total number of cards in the game

    // Add raw pointers from each card pool
    for (const auto &[type, cardVec] : cards)
    {
        for (const auto &card : cardVec)
        {
            allCards.push_back(card.get());
        }
    }

    // Shuffle the cards using a random number generator
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(allCards.begin(), allCards.end(), std::default_random_engine(seed));

    // Create and return a new deck with the shuffled cards
    Deck deck;
    deck.insert(deck.begin(), allCards.begin(), allCards.end());

    return deck;
}

Card *CardFactory::createCard(const std::string &cardName)
{
    if (cards.find(cardName) != cards.end() && !cards[cardName].empty())
    {
        if (cardName == "Blue")
            return BeanCreator<Blue>::create();
        if (cardName == "Chili")
            return BeanCreator<Chili>::create();
        if (cardName == "Stink")
            return BeanCreator<Stink>::create();
        if (cardName == "Green")
            return BeanCreator<Green>::create();
        if (cardName == "Soy")
            return BeanCreator<Soy>::create();
        if (cardName == "Black")
            return BeanCreator<Black>::create();
        if (cardName == "Red")
            return BeanCreator<Red>::create();
        if (cardName == "Garden")
            return BeanCreator<Garden>::create();
    }

    throw std::runtime_error("Unable to create card: " + cardName);
}