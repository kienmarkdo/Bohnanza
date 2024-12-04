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
    virtual const Card *getFirstCard() const = 0;
};

template <typename T>
class Chain : public Chain_Base
{
    static_assert(std::is_base_of<Card, T>::value, "Template parameter must be derived from Card");

public:
    Chain() = default;
    Chain(std::istream &in, const CardFactory *factory);

    Chain(Chain &&) noexcept = default;
    Chain &operator=(Chain &&) noexcept = default;

    Chain(const Chain &) = delete;
    Chain &operator=(const Chain &) = delete;

    Chain_Base &operator+=(std::unique_ptr<Card> card) override
    {
        if (auto *typedCard = dynamic_cast<T *>(card.get()))
        {
            cards.push_back(std::unique_ptr<T>(static_cast<T *>(card.release())));
            return *this;
        }
        throw IllegalType();
    }

    const Card *getFirstCard() const override
    {
        return cards.empty() ? nullptr : cards[0].get();
    }

    int sell() override
    {
        if (cards.empty())
            return 0;

        int numCards = cards.size();
        const T *card = static_cast<const T *>(cards[0].get());

        for (int coins = 4; coins > 0; --coins)
        {
            if (numCards >= card->getCardsPerCoin(coins))
            {
                return coins;
            }
        }
        return 0;
    }

    int size() const override { return cards.size(); }

    std::string getType() const override
    {
        if (!cards.empty())
        {
            return cards[0]->getName();
        }

        if (std::is_same<T, Blue>::value)
        {
            return "Blue";
        }
        else if (std::is_same<T, Chili>::value)
        {
            return "Chili";
        }
        else if (std::is_same<T, Green>::value)
        {
            return "Green";
        }
        else if (std::is_same<T, Soy>::value)
        {
            return "Soy";
        }
        else if (std::is_same<T, Black>::value)
        {
            return "Black";
        }
        else if (std::is_same<T, Red>::value)
        {
            return "Red";
        }
        else if (std::is_same<T, Garden>::value)
        {
            return "Garden";
        }
        else
        {
            return "Unknown";
        }
    }

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

    ~Chain() = default;

private:
    std::vector<std::unique_ptr<T>> cards;
};

#endif // CHAIN_H