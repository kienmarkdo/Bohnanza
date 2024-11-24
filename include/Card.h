#ifndef CARD_H
#define CARD_H

#include <string>
#include <ostream>
#include <iostream> // Add this for cout, cerr

// Forward declaration
class CardFactory;

class Card
{
public:
    virtual int getCardsPerCoin(int coins) const = 0;
    virtual std::string getName() const = 0;
    virtual void print(std::ostream &out) const = 0;

    Card(const Card &) = delete;
    Card &operator=(const Card &) = delete;

    friend std::ostream &operator<<(std::ostream &out, const Card &card);

    virtual ~Card()
    {
        try
        {
            std::cout << "Card destructor called\n"; // Remove getName() call
        }
        catch (...)
        {
            std::cerr << "Error in Card destructor\n";
        }
    }

protected:
    Card() = default;
};

// Base factory method for beans
template <typename T>
class BeanCreator
{
    friend class CardFactory;

public:
    static T *create()
    {
        return new T();
    }

private:
    BeanCreator() = default;
};

class Blue : public Card
{
    friend class BeanCreator<Blue>;

public:
    int getCardsPerCoin(int coins) const override;
    std::string getName() const override { return "Blue"; }
    void print(std::ostream &out) const override { out << 'B'; }

private:
    Blue() = default;
};

class Chili : public Card
{
    friend class BeanCreator<Chili>;

public:
    int getCardsPerCoin(int coins) const override;
    std::string getName() const override { return "Chili"; }
    void print(std::ostream &out) const override { out << 'C'; }

private:
    Chili() = default;
};

class Stink : public Card
{
    friend class BeanCreator<Stink>;

public:
    int getCardsPerCoin(int coins) const override;
    std::string getName() const override { return "Stink"; }
    void print(std::ostream &out) const override { out << 'S'; }

private:
    Stink() = default;
};

class Green : public Card
{
    friend class BeanCreator<Green>;

public:
    int getCardsPerCoin(int coins) const override;
    std::string getName() const override { return "Green"; }
    void print(std::ostream &out) const override { out << 'G'; }

private:
    Green() = default;
};

class Soy : public Card
{
    friend class BeanCreator<Soy>;

public:
    int getCardsPerCoin(int coins) const override;
    std::string getName() const override { return "Soy"; }
    void print(std::ostream &out) const override { out << 's'; }

private:
    Soy() = default;
};

class Black : public Card
{
    friend class BeanCreator<Black>;

public:
    int getCardsPerCoin(int coins) const override;
    std::string getName() const override { return "Black"; }
    void print(std::ostream &out) const override { out << 'B'; }

private:
    Black() = default;
};

class Red : public Card
{
    friend class BeanCreator<Red>;

public:
    int getCardsPerCoin(int coins) const override;
    std::string getName() const override { return "Red"; }
    void print(std::ostream &out) const override { out << 'R'; }

private:
    Red() = default;
};

class Garden : public Card
{
    friend class BeanCreator<Garden>;

public:
    int getCardsPerCoin(int coins) const override;
    std::string getName() const override { return "Garden"; }
    void print(std::ostream &out) const override { out << 'G'; }

private:
    Garden() = default;
};

#endif // CARD_H