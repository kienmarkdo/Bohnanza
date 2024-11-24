#ifndef CHAIN_H
#define CHAIN_H

#include <vector>
#include <string>
#include <iostream>
#include "Card.h"

// Forward declaration
class CardFactory;

// Custom exception for illegal card types
class IllegalType : public std::exception
{
public:
    const char *what() const noexcept override
    {
        return "Attempted to add wrong card type to chain";
    }
};

// Abstract base class for chains
class Chain_Base
{
public:
    virtual ~Chain_Base() = default;
    virtual int sell() = 0;
    virtual void serialize(std::ostream &out) const = 0;
    virtual void print(std::ostream &out) const = 0;
    virtual int size() const = 0;

    virtual std::string getType() const = 0;
};

template <typename T>
class Chain : public Chain_Base
{
    static_assert(std::is_base_of<Card, T>::value, "Template parameter must be derived from Card");

public:
    // Default constructor
    Chain() = default;
    ~Chain()
    {
        this->clear();
    }
    // Constructor to reconstruct chain from file
    Chain(std::istream &in, const CardFactory *factory);

    Chain<T> &operator+=(Card *card);
    void serialize(std::ostream &out) const override
    {
        // Save chain type
        out << T().getName() << "\n"; // Create temporary T to get name

        // Save number of cards (optional, but helpful)
        out << this->size() << "\n";

        // Save cards in chain
        for (const Card *card : *this)
        {
            if (card)
            {
                out << card->getName() << "\n";
            }
        }
        out << "END_CHAIN\n";
    } // Add card to the chain
    // Count cards and return number of coins
    int sell() override;

    // Return number of cards in chain
    int size() const override { return cards.size(); }

    // Get chain type
    std::string getType() const override
    {
        if (!cards.empty())
        {
            return cards[0]->getName();
        }
        // Instead of creating a temporary object, use type traits
        if (std::is_same<T, Blue>::value)
            return "Blue";
        if (std::is_same<T, Chili>::value)
            return "Chili";
        if (std::is_same<T, Stink>::value)
            return "Stink";
        if (std::is_same<T, Green>::value)
            return "Green";
        if (std::is_same<T, Soy>::value)
            return "Soy";
        if (std::is_same<T, Black>::value)
            return "Black";
        if (std::is_same<T, Red>::value)
            return "Red";
        if (std::is_same<T, Garden>::value)
            return "Garden";
        return "Unknown";
    }

    // Print function
    void print(std::ostream &out) const override
    {
        out << getType() << " ";
        for (const auto &card : cards)
        {
            card->print(out);
            out << " ";
        }
    }

    // Stream insertion operator
    friend std::ostream &operator<<(std::ostream &out, const Chain<T> &chain)
    {
        chain.print(out);
        return out;
    }

    // Destructor
    // ~Chain()
    // {
    //     for (auto card : cards)
    //     {
    //         delete card;
    //     }
    // }

    // Delete copy operations
    Chain(const Chain &) = delete;
    Chain &operator=(const Chain &) = delete;

    // Move operations
    Chain(Chain &&other) noexcept : cards(std::move(other.cards))
    {
        other.cards.clear();
    }

    Chain &operator=(Chain &&other) noexcept
    {
        if (this != &other)
        {
            for (auto card : cards)
            {
                delete card;
            }
            cards = std::move(other.cards);
            other.cards.clear();
        }
        return *this;
    }

private:
    std::vector<T *> cards;
};

// Template implementation
template <typename T>
Chain<T> &Chain<T>::operator+=(Card *card)
{
    T *typedCard = dynamic_cast<T *>(card);
    if (!typedCard)
    {
        throw IllegalType();
    }
    cards.push_back(typedCard);
    return *this;
}

template <typename T>
int Chain<T>::sell()
{
    if (cards.empty())
        return 0;

    T *sampleCard = cards[0];
    int numCards = cards.size();

    for (int coins = 4; coins > 0; --coins)
    {
        if (numCards >= sampleCard->getCardsPerCoin(coins))
        {
            return coins;
        }
    }
    return 0;
}

template <typename T>
Chain<T>::Chain(std::istream &in, const CardFactory *factory)
{
    cards.clear();
}

#endif // CHAIN_H
