#ifndef CARD_H
#define CARD_H

#include <string>
#include <iostream>

/**
 * @class Card
 * @brief Abstract base class representing a bean card.
 * 
 * A Card represents one of several bean types. Derived classes implement:
 * - getCardsPerCoin: how many cards needed for certain number of coins.
 * - getName: full bean name.
 * - print: print a character representing the bean.
 */
class Card {
public:
    virtual ~Card() = default;
    virtual int getCardsPerCoin(int coins) const = 0;
    virtual std::string getName() const = 0;
    virtual void print(std::ostream& out) const = 0;
    friend std::ostream& operator<<(std::ostream& out, const Card& card);
};

/**
 * @class Blue
 * @brief Derived card type: Blue bean.
 */
class Blue : public Card {
public:
    int getCardsPerCoin(int coins) const override;
    std::string getName() const override;
    void print(std::ostream& out) const override;
};

/**
 * @class Chili
 * @brief Derived card type: Chili bean.
 */
class Chili : public Card {
public:
    int getCardsPerCoin(int coins) const override;
    std::string getName() const override;
    void print(std::ostream& out) const override;
};

/**
 * @class Stink
 * @brief Derived card type: Stink bean.
 */
class Stink : public Card {
public:
    int getCardsPerCoin(int coins) const override;
    std::string getName() const override;
    void print(std::ostream& out) const override;
};

/**
 * @class Green
 * @brief Derived card type: Green bean.
 */
class Green : public Card {
public:
    int getCardsPerCoin(int coins) const override;
    std::string getName() const override;
    void print(std::ostream& out) const override;
};

/**
 * @class Soy
 * @brief Derived card type: Soy bean.
 */
class Soy : public Card {
public:
    int getCardsPerCoin(int coins) const override;
    std::string getName() const override;
    void print(std::ostream& out) const override;
};

/**
 * @class Black
 * @brief Derived card type: Black bean.
 */
class Black : public Card {
public:
    int getCardsPerCoin(int coins) const override;
    std::string getName() const override;
    void print(std::ostream& out) const override;
};

/**
 * @class Red
 * @brief Derived card type: Red bean.
 */
class Red : public Card {
public:
    int getCardsPerCoin(int coins) const override;
    std::string getName() const override;
    void print(std::ostream& out) const override;
};

/**
 * @class Garden
 * @brief Derived card type: Garden bean.
 */
class Garden : public Card {
public:
    int getCardsPerCoin(int coins) const override;
    std::string getName() const override;
    void print(std::ostream& out) const override;
};

#endif
