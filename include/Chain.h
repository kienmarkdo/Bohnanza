#ifndef CHAIN_H
#define CHAIN_H

#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include <limits>
#include "Card.h"
#include "CardFactory.h"
#include <type_traits>

/**
 * @brief Exception thrown when attempting to add a card of a wrong type to a chain.
 */
class IllegalType : public std::exception {
public:
    const char *what() const noexcept override {
        return "Attempted to add wrong card type to chain";
    }
};

/**
 * @brief Chain_Base is an abstract base class representing a chain of bean cards of a single type.
 *        It provides methods to sell the chain, serialize it, print it, and access its size and type.
 */
class Chain_Base {
public:
    virtual ~Chain_Base() = default;

    /**
     * @brief Calculate how many coins the current chain would yield if sold.
     * @return The number of coins obtained from selling this chain.
     */
    virtual int sell() = 0;

    /**
     * @brief Serialize the chain to an output stream for saving the game.
     * @param out The output stream to write the chain data to.
     */
    virtual void serialize(std::ostream &out) const = 0;

    /**
     * @brief Print the chain contents (type and cards).
     * @param out The output stream to print to.
     */
    virtual void print(std::ostream &out) const = 0;

    /**
     * @brief Get the number of cards currently in the chain.
     * @return The number of cards.
     */
    virtual int size() const = 0;

    /**
     * @brief Get the bean type of the chain.
     * @return The bean type as a string (e.g. "Blue").
     */
    virtual std::string getType() const = 0;

    /**
     * @brief Add a card to the chain.
     * @param card The card to add.
     * @return A reference to the chain (for chaining operations).
     * @throws IllegalType if the card type doesn't match the chain type.
     */
    virtual Chain_Base &operator+=(std::unique_ptr<Card> card) = 0;

    /**
     * @brief Get a pointer to the first card in the chain, or nullptr if empty.
     */
    virtual const Card *getFirstCard() const = 0;
};

/**
 * @brief The Chain class template represents a chain of a specific bean card type T.
 *        It enforces type-checking for added cards and provides logic to determine the chain's value.
 */
template <typename T>
class Chain : public Chain_Base {
    static_assert(std::is_base_of<Card, T>::value, "Template parameter must be derived from Card");

public:
    Chain() = default;

    /**
     * @brief Construct a Chain by loading its state from an input stream.
     *        The chain type line is assumed to be already read by the caller.
     * @param in Input stream containing saved chain data.
     * @param factory The CardFactory used to recreate cards.
     */
    Chain(std::istream &in, const CardFactory *factory) {
        int chainSize;
        in >> chainSize;
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        for (int i = 0; i < chainSize; ++i) {
            std::string cardName;
            std::getline(in, cardName);
            if (!cardName.empty()) {
                auto card = factory->getFactory()->createCard(cardName);
                auto *typedCard = dynamic_cast<T*>(card.get());
                if (!typedCard) {
                    throw IllegalType();
                }
                cards.push_back(std::unique_ptr<T>(static_cast<T*>(card.release())));
            }
        }

        std::string endChain;
        std::getline(in, endChain);
        if (endChain != "END_CHAIN") {
            throw std::runtime_error("Invalid chain format: missing END_CHAIN");
        }
    }

    Chain(Chain &&) noexcept = default;
    Chain &operator=(Chain &&) noexcept = default;

    Chain(const Chain &) = delete;
    Chain &operator=(const Chain &) = delete;

    Chain_Base &operator+=(std::unique_ptr<Card> card) override {
        if (auto *typedCard = dynamic_cast<T*>(card.get())) {
            cards.push_back(std::unique_ptr<T>(static_cast<T*>(card.release())));
            return *this;
        }
        throw IllegalType();
    }

    const Card *getFirstCard() const override {
        return cards.empty() ? nullptr : cards[0].get();
    }

    int sell() override {
        if (cards.empty())
            return 0;

        int numCards = static_cast<int>(cards.size());
        const T *card = static_cast<const T *>(cards[0].get());

        for (int coins = 4; coins > 0; --coins) {
            if (numCards >= card->getCardsPerCoin(coins)) {
                return coins;
            }
        }
        return 0;
    }

    int size() const override { return static_cast<int>(cards.size()); }

    std::string getType() const override {
        if (!cards.empty()) {
            return cards[0]->getName();
        }

        // If empty, determine type by T
        if (std::is_same<T, Blue>::value) {
            return "Blue";
        } else if (std::is_same<T, Chili>::value) {
            return "Chili";
        } else if (std::is_same<T, Green>::value) {
            return "Green";
        } else if (std::is_same<T, Soy>::value) {
            return "Soy";
        } else if (std::is_same<T, Black>::value) {
            return "Black";
        } else if (std::is_same<T, Red>::value) {
            return "Red";
        } else if (std::is_same<T, Garden>::value) {
            return "Garden";
        } else {
            return "Unknown";
        }
    }

    void print(std::ostream &out) const override {
        out << getType() << " ";
        for (const auto &card : cards) {
            card->print(out);
            out << " ";
        }
    }

    void serialize(std::ostream &out) const override {
        out << getType() << "\n";
        out << size() << "\n";
        for (const auto &card : cards) {
            out << card->getName() << "\n";
        }
        out << "END_CHAIN\n";
    }

    ~Chain() = default;

private:
    std::vector<std::unique_ptr<T>> cards;
};

#endif // CHAIN_H
