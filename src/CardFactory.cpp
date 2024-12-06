#include "CardFactory.h"
#include <algorithm>
#include <random>
#include <chrono>
#include <stdexcept>

std::shared_ptr<CardFactory> CardFactory::instance = nullptr;

/**
 * @brief CardFactory constructor initializes the card pools.
 */
CardFactory::CardFactory()
{
    initializeCards();
}

/**
 * @brief Retrieve the singleton CardFactory instance.
 * @return Shared pointer to the CardFactory.
 */
std::shared_ptr<CardFactory> CardFactory::getFactory()
{
    if (!instance)
    {
        instance = std::shared_ptr<CardFactory>(new CardFactory());
    }
    return instance;
}

/**
 * @brief Initialize all card pools with their respective counts.
 *        Creates a map of card types to multiple instances.
 */
void CardFactory::initializeCards()
{
    auto createCards = [this](const std::string &type, int count, auto creator)
    {
        cards[type].reserve(count);
        for (int i = 0; i < count; ++i)
        {
            cards[type].push_back(std::unique_ptr<Card>(creator()));
        }
    };

    // Initialize each bean type with the required counts
    createCards("Blue", 20, BeanCreator<Blue>::create);
    createCards("Chili", 18, BeanCreator<Chili>::create);
    createCards("Stink", 16, BeanCreator<Stink>::create);
    createCards("Green", 14, BeanCreator<Green>::create);
    createCards("Soy", 12, BeanCreator<Soy>::create);
    createCards("Black", 10, BeanCreator<Black>::create);
    createCards("Red", 8, BeanCreator<Red>::create);
    createCards("Garden", 6, BeanCreator<Garden>::create);
}

/**
 * @brief Create a new Deck containing all the cards, then shuffle it.
 * @return A unique_ptr to the created, shuffled Deck.
 */
std::unique_ptr<Deck> CardFactory::getDeck()
{
    auto deck = std::make_unique<Deck>();
    std::vector<std::unique_ptr<Card>> allCards;
    allCards.reserve(104); // Total number of cards

    for (const auto &pair : cards)
    {
        const auto &cardVec = pair.second;
        for (const auto &card : cardVec)
        {
            allCards.push_back(std::unique_ptr<Card>(card->clone()));
        }
    }

    // Shuffle using current time as seed
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(allCards.begin(), allCards.end(), std::default_random_engine(seed));

    for (auto &card : allCards)
    {
        deck->addCard(std::move(card));
    }

    return deck;
}

/**
 * @brief Create a single card by its name, used during game loading.
 * @param cardName Name of the card to create.
 * @return A unique_ptr to the newly created card.
 * @throws std::runtime_error if the card name is invalid.
 */
std::unique_ptr<Card> CardFactory::createCard(const std::string &cardName)
{
    auto createSpecificCard = [](const std::string &name) -> std::unique_ptr<Card>
    {
        if (name == "Blue")   return BeanCreator<Blue>::create();
        if (name == "Chili")  return BeanCreator<Chili>::create();
        if (name == "Stink")  return BeanCreator<Stink>::create();
        if (name == "Green")  return BeanCreator<Green>::create();
        if (name == "Soy")    return BeanCreator<Soy>::create();
        if (name == "Black")  return BeanCreator<Black>::create();
        if (name == "Red")    return BeanCreator<Red>::create();
        if (name == "Garden") return BeanCreator<Garden>::create();
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
