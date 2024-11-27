#include "CardFactory.h"
#include <algorithm>
#include <random>
#include <chrono>
#include <stdexcept>

std::shared_ptr<CardFactory> CardFactory::instance = nullptr;

CardFactory::CardFactory()
{
    initializeCards();
}

std::shared_ptr<CardFactory> CardFactory::getFactory()
{
    if (!instance)
    {
        instance = std::shared_ptr<CardFactory>(new CardFactory());
    }
    return instance;
}

void CardFactory::initializeCards()
{
    // Initialize all card pools according to the game requirements
    auto createCards = [this](const std::string &type, int count, auto creator)
    {
        cards[type].reserve(count);
        for (int i = 0; i < count; ++i)
        {
            cards[type].push_back(std::unique_ptr<Card>(creator()));
        }
    };

    createCards("Blue", 20, BeanCreator<Blue>::create);
    createCards("Chili", 18, BeanCreator<Chili>::create);
    createCards("Stink", 16, BeanCreator<Stink>::create);
    createCards("Green", 14, BeanCreator<Green>::create);
    createCards("Soy", 12, BeanCreator<Soy>::create);
    createCards("Black", 10, BeanCreator<Black>::create);
    createCards("Red", 8, BeanCreator<Red>::create);
    createCards("Garden", 6, BeanCreator<Garden>::create);
}

std::unique_ptr<Deck> CardFactory::getDeck()
{
    auto deck = std::make_unique<Deck>();
    std::vector<std::unique_ptr<Card>> allCards;
    allCards.reserve(104); // Total number of cards in the game

    // Move cards from each pool to temporary vector
    for (const auto &[type, cardVec] : cards)
    {
        for (const auto &card : cardVec)
        {
            allCards.push_back(std::unique_ptr<Card>(card->clone()));
        }
    }

    // Shuffle the cards using a random number generator
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(allCards.begin(), allCards.end(), std::default_random_engine(seed));

    // Move cards to the deck
    for (auto &card : allCards)
    {
        deck->addCard(std::move(card));
    }

    return deck;
}

std::unique_ptr<Card> CardFactory::createCard(const std::string &cardName)
{
    auto createSpecificCard = [](const std::string &name) -> std::unique_ptr<Card>
    {
        if (name == "Blue")
            return std::unique_ptr<Card>(BeanCreator<Blue>::create());
        if (name == "Chili")
            return std::unique_ptr<Card>(BeanCreator<Chili>::create());
        if (name == "Stink")
            return std::unique_ptr<Card>(BeanCreator<Stink>::create());
        if (name == "Green")
            return std::unique_ptr<Card>(BeanCreator<Green>::create());
        if (name == "Soy")
            return std::unique_ptr<Card>(BeanCreator<Soy>::create());
        if (name == "Black")
            return std::unique_ptr<Card>(BeanCreator<Black>::create());
        if (name == "Red")
            return std::unique_ptr<Card>(BeanCreator<Red>::create());
        if (name == "Garden")
            return std::unique_ptr<Card>(BeanCreator<Garden>::create());
        return nullptr;
    };

    if (cards.find(cardName) != cards.end())
    {
        auto card = createSpecificCard(cardName);
        if (card)
            return card;
    }

    throw std::runtime_error("Unable to create card: " + cardName);
}