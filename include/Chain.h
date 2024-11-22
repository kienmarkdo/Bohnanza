// Chain.h
#ifndef CHAIN_H
#define CHAIN_H

#include "Chain_Base.h"
#include "Card.h"
#include "CardFactory.h"
#include <vector>
#include <sstream>
#include <typeinfo>

class IllegalTypeException : public std::exception
{
    virtual const char *what() const throw()
    {
        return "IllegalTypeException";
    }
};
template <typename T>
class Chain : public Chain_Base
{
private:
    std::vector<T *> cards;

public:
    // Default constructor
    Chain() = default;

    // Constructor from istream to reconstruct the chain
    Chain(std::istream &in, const CardFactory *factory)
    {
        std::string beanName;
        in >> beanName; // Read the bean name

        std::string line;
        std::getline(in, line);
        std::istringstream iss(line);
        std::string token;
        while (iss >> token)
        {
            // Assuming tokens are single-character representations of cards
            Card *card = factory->getCard(token[0]); // Get card from factory
            T *tcard = dynamic_cast<T *>(card);
            if (tcard)
            {
                cards.push_back(tcard);
            }
            else
            {
                throw IllegalType(); // Throw exception if type doesn't match
            }
        }
    }

    // Adds a card to the Chain
    Chain<T> &operator+=(Card *card)
    {
        T *tcard = dynamic_cast<T *>(card);
        if (tcard)
        {
            cards.push_back(tcard);
            return *this;
        }
        else
        {
            throw IllegalType();
        }
    }

    // Counts the cards and returns the number of coins earned
    int sell() override
    {
        int numCards = static_cast<int>(cards.size());
        if (numCards == 0)
        {
            return 0;
        }

        T tempCard;
        int coins = tempCard.getCoinsForCards(numCards);

        // Clear the cards from the chain (do not delete as CardFactory manages them)
        cards.clear();

        return coins;
    }

    // Prints the chain to the output stream
    void print(std::ostream &out) const override
    {
        if (cards.empty())
        {
            return;
        }
        T tempCard;
        out << tempCard.getName() << " ";
        for (const auto &card : cards)
        {
            card->print(out);
            out << " ";
        }
    }
};

template <typename T>
std::ostream &operator<<(std::ostream &out, const Chain<T> &chain)
{
    chain.print(out);
    return out;
}

#endif // CHAIN_H