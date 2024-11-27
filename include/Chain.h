#ifndef CHAIN_H
#define CHAIN_H

#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include "Card.h"
#include "CardFactory.h"
class CardFactory;
#include <type_traits>
class IllegalType : public std::exception
{
public:
    const char *what() const noexcept override
    {
        return "Attempted to add wrong card type to chain";
    }
};

class Chain_Base
{
public:
    virtual ~Chain_Base() = default;
    virtual int sell() = 0;
    virtual void serialize(std::ostream &out) const = 0;
    virtual void print(std::ostream &out) const = 0;
    virtual int size() const = 0;
    virtual std::string getType() const = 0;
    virtual Chain_Base &operator+=(std::unique_ptr<Card> card) = 0;
};

template <typename T>
class Chain : public Chain_Base
{
    static_assert(std::is_base_of<Card, T>::value, "Template parameter must be derived from Card");

public:
    // Constructors
    Chain() = default;
    Chain(std::istream &in, const CardFactory *factory);

    // Move operations
    Chain(Chain &&) noexcept = default;
    Chain &operator=(Chain &&) noexcept = default;

    // Delete copy operations
    Chain(const Chain &) = delete;
    Chain &operator=(const Chain &) = delete;

    // Core functionality
    Chain_Base &operator+=(std::unique_ptr<Card> card) override
    {
        if (auto *typedCard = dynamic_cast<T *>(card.get()))
        {
            cards.push_back(std::unique_ptr<T>(static_cast<T *>(card.release())));
            return *this;
        }
        throw IllegalType();
    }

    int sell() override
    {
        if (cards.empty())
            return 0;

        int numCards = cards.size();
        for (int coins = 4; coins > 0; --coins)
        {
            if (numCards >= cards.front()->getCardsPerCoin(coins))
            {
                return coins;
            }
        }
        return 0;
    }

    // Getters
    int size() const override { return cards.size(); }

    std::string getType() const override
    {
        if (!cards.empty())
        {
            return cards[0]->getName();
        }

        // Changed conditions to use the proper syntax
        if constexpr (std::is_same_v<T, Blue>())
            return "Blue";
        if constexpr (std::is_same_v<T, Chili>())
            return "Stink";
        if constexpr (std::is_same_v<T, Green>())
            return "Green";
        if constexpr (std::is_same_v<T, Soy>())
            return "Soy";
        if constexpr (std::is_same_v<T, Black>())
            return "Black";
        if constexpr (std::is_same_v<T, Red>())
            return "Red";
        if constexpr (std::is_same_v<T, Garden>())
            return "Garden";
        return "Unknown";
    }

    // Display methods
    void print(std::ostream &out) const override
    {
        out << getType() << " ";
        for (const auto &card : cards)
        {
            card->print(out);
            out << " ";
        }
    }

    void serialize(std::ostream &out) const override
    {
        out << getType() << "\n";
        out << size() << "\n";
        for (const auto &card : cards)
        {
            out << card->getName() << "\n";
        }
        out << "END_CHAIN\n";
    }

    friend std::ostream &operator<<(std::ostream &out, const Chain &chain)
    {
        chain.print(out);
        return out;
    }

    // Destructor can be defaulted since using smart pointers
    ~Chain() = default;

private:
    std::vector<std::unique_ptr<T>> cards;
};

// Constructor implementation
template <typename T>
Chain<T>::Chain(std::istream &in, const CardFactory *factory)
{
    cards.clear();
    std::string cardName;
    int numCards;
    in >> numCards;

    for (int i = 0; i < numCards; ++i)
    {
        std::getline(in, cardName);
        if (cardName == "END_CHAIN")
            break;

        try
        {
            auto card = factory->getFactory()->createCard(cardName);
            if (auto *typedCard = dynamic_cast<T *>(card.get()))
            {
                cards.push_back(std::unique_ptr<T>(static_cast<T *>(card.release())));
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error loading chain card: " << e.what() << std::endl;
        }
    }
}

#endif // CHAIN_H