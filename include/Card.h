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

class Card
{
public:
    virtual int getCardsPerCoin(int coins) const = 0;
    virtual std::string getName() const = 0;
    virtual void print(std::ostream &out) const = 0;
    virtual std::unique_ptr<Card> clone() const = 0;

    // Delete copy operations
    Card(const Card &) = delete;
    Card &operator=(const Card &) = delete;

    friend std::ostream &operator<<(std::ostream &out, const Card &card);

    virtual ~Card()
    {
        }

protected:
    Card() = default;
};

// Bean class definitions
class Blue : public Card
{
    friend class BeanCreator<Blue>;

public:
    int getCardsPerCoin(int coins) const override;
    std::string getName() const override { return "Blue"; }
    void print(std::ostream &out) const override { out << 'B'; }
    std::unique_ptr<Card> clone() const override
    {
        auto ptr = std::unique_ptr<Blue>(new Blue());
        return ptr;
    }

private:
    Blue() = default;
};

// Do the same pattern for all other bean classes...
class Chili : public Card
{
    friend class BeanCreator<Chili>;

public:
    int getCardsPerCoin(int coins) const override;
    std::string getName() const override { return "Chili"; }
    void print(std::ostream &out) const override { out << 'C'; }
    std::unique_ptr<Card> clone() const override
    {
        auto ptr = std::unique_ptr<Chili>(new Chili());
        return ptr;
    }

private:
    Chili() = default;
};

class Soy : public Card
{
    friend class BeanCreator<Soy>;

public:
    int getCardsPerCoin(int coins) const override;
    std::string getName() const override { return "Soy"; }
    void print(std::ostream &out) const override { out << 's'; }
    std::unique_ptr<Card> clone() const override
    {
        auto ptr = std::unique_ptr<Soy>(new Soy());
        return ptr;
    }

private:
    Soy() = default;
};

class Stink : public Card
{
    friend class BeanCreator<Stink>;

public:
    int getCardsPerCoin(int coins) const override;
    std::string getName() const override { return "Stink"; }
    void print(std::ostream &out) const override { out << 'S'; }
    std::unique_ptr<Card> clone() const override
    {
        auto ptr = std::unique_ptr<Stink>(new Stink());
        return ptr;
    }

private:
    Stink() = default;
};

class Black : public Card
{
    friend class BeanCreator<Black>;

public:
    int getCardsPerCoin(int coins) const override;
    std::string getName() const override { return "Black"; }
    void print(std::ostream &out) const override { out << 'b'; }
    std::unique_ptr<Card> clone() const override
    {
        auto ptr = std::unique_ptr<Black>(new Black());
        return ptr;
    }

private:
    Black() = default;
};
class Green : public Card
{
    friend class BeanCreator<Green>;

public:
    int getCardsPerCoin(int coins) const override;
    std::string getName() const override { return "Green"; }
    void print(std::ostream &out) const override { out << 'G'; }
    std::unique_ptr<Card> clone() const override
    {
        auto ptr = std::unique_ptr<Green>(new Green());
        return ptr;
    }

private:
    Green() = default;
};

class Red : public Card
{
    friend class BeanCreator<Red>;

public:
    int getCardsPerCoin(int coins) const override;
    std::string getName() const override { return "Red"; }
    void print(std::ostream &out) const override { out << 'R'; }
    std::unique_ptr<Card> clone() const override
    {
        auto ptr = std::unique_ptr<Red>(new Red());
        return ptr;
    }

private:
    Red() = default;
};

class Garden : public Card
{
    friend class BeanCreator<Garden>;

public:
    int getCardsPerCoin(int coins) const override;
    std::string getName() const override { return "Garden"; }
    void print(std::ostream &out) const override { out << 'g'; }
    std::unique_ptr<Card> clone() const override
    {
        auto ptr = std::unique_ptr<Garden>(new Garden());
        return ptr;
    }

private:
    Garden() = default;
};

// Updated factory method for beans using smart pointers
template <typename T>
class BeanCreator
{
    friend class CardFactory;

public:
    static std::unique_ptr<T> create()
    {
        auto ptr = std::unique_ptr<T>(new T());
        return ptr;
    }

private:
    BeanCreator() = default;
};

#endif // CARD_H