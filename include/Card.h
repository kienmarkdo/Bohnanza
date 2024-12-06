#ifndef CARD_H
#define CARD_H

#include <string>
#include <ostream>
#include <iostream>
#include <memory>

// Forward declarations
class CardFactory;
template <typename T>
class BeanCreator;

/**
 * @brief The Card class is an abstract base class representing a generic bean card.
 *        It defines the interface for getting the bean's name, printing it, cloning,
 *        and determining how many cards are needed for a given number of coins.
 */
class Card {
public:
    /**
     * @brief Given a number of coins, returns how many cards of this type are required to earn that many coins.
     * @param coins The number of coins desired.
     * @return The number of cards needed for that coin value, or 0 if not applicable.
     */
    virtual int getCardsPerCoin(int coins) const = 0;

    /**
     * @brief Get the name of the card type (e.g. "Blue", "Chili").
     * @return The card's name as a string.
     */
    virtual std::string getName() const = 0;

    /**
     * @brief Print a short representation of the card to the output stream (e.g., 'B' for Blue).
     * @param out The output stream.
     */
    virtual void print(std::ostream &out) const = 0;

    /**
     * @brief Create a clone of this card, returning a unique_ptr to the new card.
     * @return A unique_ptr to a newly allocated card of the same type.
     */
    virtual std::unique_ptr<Card> clone() const = 0;

    // Delete copy operations to avoid accidental copying
    Card(const Card &) = delete;
    Card &operator=(const Card &) = delete;

    /**
     * @brief Overloaded output operator to print the card.
     */
    friend std::ostream &operator<<(std::ostream &out, const Card &card);

    virtual ~Card() {}

protected:
    Card() = default;
};

/**
 * @brief The Blue bean card class.
 *        Has specific rules for getCardsPerCoin and a print representation.
 */
class Blue : public Card {
    friend class BeanCreator<Blue>;

public:
    int getCardsPerCoin(int coins) const override;
    std::string getName() const override { return "Blue"; }
    void print(std::ostream &out) const override { out << 'B'; }
    std::unique_ptr<Card> clone() const override {
        auto ptr = std::unique_ptr<Blue>(new Blue());
        return ptr;
    }

private:
    Blue() = default;
};

/**
 * @brief The Chili bean card class.
 */
class Chili : public Card {
    friend class BeanCreator<Chili>;

public:
    int getCardsPerCoin(int coins) const override;
    std::string getName() const override { return "Chili"; }
    void print(std::ostream &out) const override { out << 'C'; }
    std::unique_ptr<Card> clone() const override {
        auto ptr = std::unique_ptr<Chili>(new Chili());
        return ptr;
    }

private:
    Chili() = default;
};

/**
 * @brief The Soy bean card class.
 */
class Soy : public Card {
    friend class BeanCreator<Soy>;

public:
    int getCardsPerCoin(int coins) const override;
    std::string getName() const override { return "Soy"; }
    void print(std::ostream &out) const override { out << 's'; }
    std::unique_ptr<Card> clone() const override {
        auto ptr = std::unique_ptr<Soy>(new Soy());
        return ptr;
    }

private:
    Soy() = default;
};

/**
 * @brief The Stink bean card class.
 */
class Stink : public Card {
    friend class BeanCreator<Stink>;

public:
    int getCardsPerCoin(int coins) const override;
    std::string getName() const override { return "Stink"; }
    void print(std::ostream &out) const override { out << 'S'; }
    std::unique_ptr<Card> clone() const override {
        auto ptr = std::unique_ptr<Stink>(new Stink());
        return ptr;
    }

private:
    Stink() = default;
};

/**
 * @brief The Black bean card class.
 */
class Black : public Card {
    friend class BeanCreator<Black>;

public:
    int getCardsPerCoin(int coins) const override;
    std::string getName() const override { return "Black"; }
    void print(std::ostream &out) const override { out << 'b'; }
    std::unique_ptr<Card> clone() const override {
        auto ptr = std::unique_ptr<Black>(new Black());
        return ptr;
    }

private:
    Black() = default;
};

/**
 * @brief The Green bean card class.
 */
class Green : public Card {
    friend class BeanCreator<Green>;

public:
    int getCardsPerCoin(int coins) const override;
    std::string getName() const override { return "Green"; }
    void print(std::ostream &out) const override { out << 'G'; }
    std::unique_ptr<Card> clone() const override {
        auto ptr = std::unique_ptr<Green>(new Green());
        return ptr;
    }

private:
    Green() = default;
};

/**
 * @brief The Red bean card class.
 */
class Red : public Card {
    friend class BeanCreator<Red>;

public:
    int getCardsPerCoin(int coins) const override;
    std::string getName() const override { return "Red"; }
    void print(std::ostream &out) const override { out << 'R'; }
    std::unique_ptr<Card> clone() const override {
        auto ptr = std::unique_ptr<Red>(new Red());
        return ptr;
    }

private:
    Red() = default;
};

/**
 * @brief The Garden bean card class.
 */
class Garden : public Card {
    friend class BeanCreator<Garden>;

public:
    int getCardsPerCoin(int coins) const override;
    std::string getName() const override { return "Garden"; }
    void print(std::ostream &out) const override { out << 'g'; }
    std::unique_ptr<Card> clone() const override {
        auto ptr = std::unique_ptr<Garden>(new Garden());
        return ptr;
    }

private:
    Garden() = default;
};

/**
 * @brief The BeanCreator class is a template used by the CardFactory
 *        to create bean card instances. It provides a static create method.
 */
template <typename T>
class BeanCreator {
    friend class CardFactory;

public:
    /**
     * @brief Create a new instance of the bean card type T.
     * @return A unique_ptr to the newly created bean card.
     */
    static std::unique_ptr<T> create() {
        auto ptr = std::unique_ptr<T>(new T());
        return ptr;
    }

private:
    BeanCreator() = default;
};

#endif // CARD_H
